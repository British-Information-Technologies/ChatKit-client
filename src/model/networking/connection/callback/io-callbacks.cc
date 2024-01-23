#include "io-callbacks.h"

#include <event2/bufferevent.h>
#include <event2/event.h>
#include <iostream>

#include "model/networking/connection/connection.h"
#include "model/networking/utility/buffer-reader.h"

using namespace model;
using namespace model_networking_connection_callback;

namespace {
void ReadMessageClientCbHandler(struct bufferevent* bev, void* ptr);
void ReadMessageServerCbHandler(struct bufferevent* bev, void* ptr);
void WriteMessageCbHandler(struct bufferevent* bev, void* ptr);
void EventCbHandler(struct bufferevent* bev, short events, void* ptr);

void ReadMessageClientCbHandler(
    struct bufferevent* bev,
    void* ptr) {
    // cast connection object
    Connection* connection = static_cast<Connection*>(ptr);

    // read packet
    std::string packet = ReadBufferLine(bev);

    if (!packet.length()) {
        // packet is empty, failed to format packet
        return;
    }

    std::cout << "[ClientCallbacks]: " << packet << std::endl;

    std::shared_ptr<Message> message(DeserializeClientStreamIn(packet));

    // send data to network manager
    connection->channel->SendData(
        connection->uuid,
        bufferevent_getfd(bev),
        message);
}

void ReadMessageServerCbHandler(
    struct bufferevent* bev,
    void* ptr) {
    // cast connection object
    Connection* connection = static_cast<Connection*>(ptr);

    // read encoded packet
    std::string packet = ReadBufferLine(bev);

    if (!packet.length()) {
        // packet is empty, failed to format packet
        return;
    }

    std::cout << "[ServerConnection]: " << packet << std::endl;

    std::shared_ptr<Message> message(DeserializeServerStreamIn(packet));

    if (message->GetType() == Type::EventError) {
        // message is not a server message, check if network message
        message.reset(DeserializeNetworkStreamIn(packet));
    }

    // send data to network manager
    connection->channel->SendData(
        connection->uuid,
        bufferevent_getfd(bev),
        message);
}

void WriteMessageCbHandler(
    struct bufferevent* bev,
    void* ptr) {
    printf("[Connection]: data successfully written to socket\n");
}

void EventCbHandler(
    struct bufferevent* bev,
    short events,
    void* ptr) {
    if (events && (BEV_EVENT_ERROR || BEV_EVENT_READING || BEV_EVENT_WRITING)) {
        printf("[Connection]: buffer event error, terminating connection!\n");
    }
}
} // namespace

void model_networking_connection_callback::SetClientConnectionCallbacks(
    struct bufferevent* bev,
    Connection* connection) {
    bufferevent_setcb(
        bev,
        ReadMessageClientCbHandler,
        WriteMessageCbHandler,
        EventCbHandler,
        connection);
}

void model_networking_connection_callback::SetServerConnectionCallbacks(
    struct bufferevent* bev,
    Connection* connection) {
    bufferevent_setcb(
        bev,
        ReadMessageServerCbHandler,
        WriteMessageCbHandler,
        EventCbHandler,
        connection);
}
