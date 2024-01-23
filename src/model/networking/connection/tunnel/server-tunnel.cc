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
    const std::string& port) : Tunnel(TunnelType::Server, connection, base, ip_address, port) {}

int ServerTunnel::SendMessage(Message* message) {
    if (
        message->GetStreamType() != StreamType::ServerStreamOut && message->GetStreamType() != StreamType::NetworkStreamOut) {
        // message must be a server stream out or network stream out
        return -1;
    }

    std::string packet = message->Serialize();

    if (!packet.length()) {
        // encoded packet is empty, failed to format message
        return -1;
    }

    // send encoded packet
    return WriteBufferLine(bev, packet);
}
