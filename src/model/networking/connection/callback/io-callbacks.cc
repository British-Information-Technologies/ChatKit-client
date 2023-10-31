#include "io-callbacks.h"

#include <event2/event.h>
#include <event2/bufferevent.h>
#include <iostream>

#include "model/networking/connection/connection.h"
#include "model/networking/utility/buffer-reader.h"

using namespace model;

void IOCallbacks::ReadMessageClientCbHandler(
  struct bufferevent *bev,
  void *ptr
)
{
  // cast connection object
  Connection *connection = static_cast<Connection*>(ptr);

  // read packet
  std::string packet = ReadBufferLine(bev);

  // decode or decode and decrypt data
  std::string plaintext = connection->ReadMessage(packet);

  if (!plaintext.length()) {
    // plaintext is empty, failed to format packet
    return;
  }

  std::cout << "[ClientCallbacks]: " << plaintext << std::endl;

  std::shared_ptr<Message> message(DeserializeClientStreamIn(plaintext));

  // send data to network manager
  connection->SendChannelMessage(message);
}

void IOCallbacks::ReadMessageServerCbHandler(
  struct bufferevent *bev,
  void *ptr
)
{
  // cast connection object
  Connection *connection = static_cast<Connection*>(ptr);
  
  // read encoded packet
  std::string encoded_packet = ReadBufferLine(bev);

  // get plaintext
  std::string plaintext = connection->ReadMessage(encoded_packet);

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
  connection->SendChannelMessage(message);
}

void IOCallbacks::WriteMessageCbHandler(
  struct bufferevent *bev,
  void *ptr
)
{
  printf("[Connection]: data successfully written to socket\n");
}

void IOCallbacks::EventCbHandler(
    struct bufferevent *bev,
    short events,
    void *ptr
)
{
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

void IOCallbacks::SetClientConnectionCallbacks(
  struct bufferevent *bev,
  Connection *connection
)
{
  bufferevent_setcb(
    bev,
    IOCallbacks::ReadMessageClientCbHandler,
    IOCallbacks::WriteMessageCbHandler,
    IOCallbacks::EventCbHandler,
    connection
  );
}

void IOCallbacks::SetServerConnectionCallbacks(
  struct bufferevent *bev,
  Connection *connection
)
{
  bufferevent_setcb(
    bev,
    IOCallbacks::ReadMessageServerCbHandler,
    IOCallbacks::WriteMessageCbHandler,
    IOCallbacks::EventCbHandler,
    connection
  );
}
