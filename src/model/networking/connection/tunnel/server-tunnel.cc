#include "msd/channel.hpp"
#include <algorithm>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <iostream>
#include <memory>
#include <netdb.h>
#include <sodium.h>
#include <string>

#include "server-tunnel.h"

#include "model/networking/connection/tunnel/tunnel.h"

#include "model/networking/messages/message.h"

#include "model/networking/utility/buffer-reader.h"
#include "model/networking/utility/buffer-writer.h"

using namespace model;

ServerTunnel::ServerTunnel(
    std::shared_ptr<Connection> connection,
    std::shared_ptr<event_base> base,
    const std::string& ip_address,
    const std::string& port,
    unsigned char* public_key,
    unsigned char* secret_key) : Tunnel(TunnelType::Server, connection, base, ip_address, port, public_key, secret_key) {}

std::unique_ptr<Tunnel> ServerTunnel::Create(
    std::shared_ptr<Connection> connection,
    std::shared_ptr<struct event_base> base,
    const std::string& ip_address,
    const std::string& port) {
    auto [public_key, secret_key] = GenerateKeyPair();

    if (public_key == nullptr || public_key == nullptr) {
        return nullptr;
    }

    // todo: refactor GenerateKeyPair and unique_ptr below to be more efficient
    std::unique_ptr<Tunnel> tunnel(new ServerTunnel(
        connection,
        base,
        ip_address,
        port,
        public_key,
        secret_key));

    return tunnel;
}

int ServerTunnel::SendMessage(Message* message) {
    if (
        message->GetStreamType() != StreamType::ServerStreamOut && message->GetStreamType() != StreamType::NetworkStreamOut) {
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
