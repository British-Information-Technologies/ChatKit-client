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

#include "client-connection.h"

#include "model/networking/messages/message.h"

#include "model/networking/utility/secure-data-handler.h"

#include "model/networking/utility/buffer-writer.h"
#include "model/networking/utility/buffer-reader.h"

using namespace model;

using json = nlohmann::json;

int ClientConnection::GetRecipientPublicKey(unsigned char* recv_pk) {
  return 0;
}

ClientConnection::ClientConnection(
    std::shared_ptr<event_base> base,
    msd::channel<json> &network_manager_chann,
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