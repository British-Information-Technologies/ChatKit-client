#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <netdb.h>
#include <string>
#include <memory>
#include <algorithm>
#include <sodium.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <nlohmann/json.hpp>
#include "msd/channel.hpp"

#include "server-connection.h"

#include "model/networking/messages/message.h"

#include "model/networking/utility/secure-data-handler.h"

#include "model/networking/utility/buffer-writer.h"
#include "model/networking/utility/buffer-reader.h"

using namespace model;

using json = nlohmann::json;

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
  std::shared_ptr<event_base> base,
  msd::channel<json> &network_manager_chann,
  const std::string &ip_address,
  const std::string &port
): Connection(base, network_manager_chann, ip_address, port) {}

int ServerConnection::SendMessage(Message *message) {
  if (
    message->GetStreamType() != StreamType::ServerStreamOut ||
    message->GetStreamType() != StreamType::NetworkStreamOut
  ) {
    // message must be a server stream out or network stream out
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