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
#include <iostream>

#include "client-tunnel.h"

#include "model/networking/connection/tunnel/tunnel.h"

#include "model/networking/messages/message.h"

#include "model/networking/utility/buffer-writer.h"
#include "model/networking/utility/buffer-reader.h"

using namespace model;

ClientTunnel::ClientTunnel(
    std::shared_ptr<Connection> connection,
    const std::string &uuid,
    std::shared_ptr<event_base> base,
    const std::string &ip_address,
    const std::string &port,
    unsigned char *public_key,
    unsigned char *secret_key
): Tunnel(TunnelType::Client, connection, uuid, base, ip_address, port, public_key, secret_key)
{}

std::unique_ptr<Tunnel> ClientTunnel::Create(
  std::shared_ptr<Connection> connection,
  const std::string &uuid,
  std::shared_ptr<struct event_base> base,
  const std::string &ip_address,
  const std::string &port
)
{
  auto [public_key, secret_key] = GenerateKeyPair();

  if (public_key == nullptr || secret_key == nullptr) {
    return nullptr;
  }

  std::unique_ptr<Tunnel> tunnel(new ClientTunnel(
    connection,
    uuid,
    base,
    ip_address,
    port,
    public_key,
    secret_key
  ));

  return tunnel;
}

int ClientTunnel::SendMessage(Message *message)
{
  if (message->GetStreamType() != StreamType::ClientStreamOut) {
    // message must be a client stream out
    return -1;
  }

  std::string msg_str = message->Serialize();
  std::string packet = data_handler->FormatSend(msg_str);
  
  if (!packet.length()) {
    // packet is empty, failed to format message
    return -1;
  }

  // send packet
  return WriteBufferLine(bev, packet);
}
