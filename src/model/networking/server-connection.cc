#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <netdb.h>
#include <string>
#include <memory>
#include <algorithm>
#include <sodium.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <iostream>
#include "msd/channel.hpp"

#include "server-connection.h"

#include "model/networking/messages/message.h"

#include "model/networking/utility/data.h"
#include "model/networking/utility/buffer-writer.h"
#include "model/networking/utility/buffer-reader.h"

using namespace model;

int ServerConnection::GetRecipientPublicKey(unsigned char* recv_pk) {
  // read potential PK - todo
  // auto server_pk_msg = ReadMessage();
  
  // json server_pk_json = server_pk_msg->ToJson();

  // verify read message is a PK
  // if (!server_pk_json.contains("PublicKey")) {
    // read message is not a PK message
    // return -1;
  // }
  
  // extract PK -- TODO

  // verify PK with CA -- TODO

  // put server PK into output buffer for return use
  // *recv_pk = server_pk_json.at("PublicKey");

  return 0;
}

ServerConnection::ServerConnection(
  const std::string &uuid,
  std::shared_ptr<event_base> base,
  msd::channel<Data> &network_manager_chann,
  const std::string &ip_address,
  const std::string &port,
  unsigned char *public_key,
  unsigned char *secret_key
): Connection(uuid, base, network_manager_chann, ip_address, port, public_key, secret_key) {}

std::shared_ptr<Connection> ServerConnection::Create(
  const std::string &uuid,
  std::shared_ptr<struct event_base> base,
  msd::channel<Data> &network_manager_chann,
  const std::string &ip_address,
  const std::string &port
) {
  auto [public_key, secret_key] = GenerateKeyPair();
  
  if (public_key == nullptr || public_key == nullptr) {
    return nullptr;
  }

  std::shared_ptr<Connection> conn(new ServerConnection(
    uuid,
    base,
    network_manager_chann,
    ip_address,
    port,
    public_key,
    secret_key
  ));

  return conn;
}

int ServerConnection::SendMessage(Message *message) {
  if (
    message->GetStreamType() != StreamType::ServerStreamOut &&
    message->GetStreamType() != StreamType::NetworkStreamOut
  ) {
    // message must be a server stream out or network stream out
    return -1;
  }
  
  std::string msg_str = message->Serialize();
  std::string packet = data_handler->FormatSend(msg_str);
  
  if (!packet.length()) {
    // encoded packet is empty, failed to format message
    return -1;
  }

  // send encoded packet
  return WriteBufferLine(bev, packet);
}

void ServerConnection::ReadMessageCb() {
  // read encoded packet
  std::string encoded_packet = ReadBufferLine(bev);

  // get plaintext
  std::string plaintext = data_handler->FormatRead(encoded_packet);

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
  SendChannelMessage(message);
}