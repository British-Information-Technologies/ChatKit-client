#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <netdb.h>
#include <string>
#include <memory>
#include <algorithm>
#include <sodium.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include "msd/channel.hpp"

#include "client-connection.h"

#include "model/networking/messages/message.h"

#include "model/networking/utility/secure-data-handler.h"

#include "model/networking/utility/data.h"
#include "model/networking/utility/buffer-writer.h"
#include "model/networking/utility/buffer-reader.h"

using namespace model;

int ClientConnection::GetRecipientPublicKey(unsigned char* recv_pk) {
  return 0;
}

ClientConnection::ClientConnection(
    std::shared_ptr<event_base> base,
    msd::channel<std::shared_ptr<Data>> &network_manager_chann,
    const std::string &ip_address,
    const std::string &port
): Connection(base, network_manager_chann, ip_address, port) {}

int ClientConnection::SendMessage(Message *message) {
  if (message->GetStreamType() != StreamType::ClientStreamOut) {
    // message must be a client stream out
    return -1;
  }

  std::string msg_str = message->Serialize();
  std::string encoded_packet = data_handler->FormatSend(msg_str);
  
  if (!encoded_packet.length()) {
    // encoded packet is empty, failed to format message
    return -1;
  }

  // send encoded packet
  return WriteBufferLine(bev, encoded_packet);
}

void ClientConnection::ReadMessageCb() {
  // read encoded packet
  std::string encoded_packet = ReadBufferLine(bev);

  // decode or decode and decrypt data
  std::string plaintext = data_handler->FormatRead(encoded_packet);

  if (!plaintext.length()) {
    // plaintext is empty, failed to format encoded packet
    return;
  }

  std::shared_ptr<Message> message;
  DeserializeClientStreamIn(message.get(), plaintext);

  // send data to network manager
  std::shared_ptr<Data> data(new Data {
    sockfd: bufferevent_getfd(bev.get()),
    message: message,
  });

  data >> out_chann;
}