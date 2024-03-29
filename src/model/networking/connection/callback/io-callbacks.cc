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

    // decode or decode and decrypt data
    std::string plaintext = connection->tunnel->ReadMessage(packet);

    if (!plaintext.length()) {
        // plaintext is empty, failed to format packet
        return;
    }

    std::cout << "[ClientCallbacks]: " << plaintext << std::endl;

    std::shared_ptr<Message> message(DeserializeClientStreamIn(plaintext));

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
    std::string encoded_packet = ReadBufferLine(bev);

    // get plaintext
    std::string plaintext = connection->tunnel->ReadMessage(encoded_packet);

    if (!plaintext.length()) {
        // plaintext is empty, failed to format encoded packet
        return;
    }

    std::cout << "[ServerConnection]: " << plaintext << std::endl;

    std::shared_ptr<Message> message(DeserializeServerStreamIn(plaintext));

    if (message->GetType() == Type::EventError) {
        // message is not a server message, check if network message
        message.reset(DeserializeNetworkStreamIn(plaintext));
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

        /* send data to network manager - todo add message factory
        json data = {
        { "sockfd", bufferevent_getfd(bev.get()) },
        { "internal", internal::EventError("Buffer Event Error! Terminating Connection!").Serialize() },
        };

        bufferevent_free(bev.get());
        
        data >> out_chann;*/
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
