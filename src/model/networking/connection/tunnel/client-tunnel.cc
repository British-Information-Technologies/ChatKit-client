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

#include "client-tunnel.h"

#include "model/networking/connection/tunnel/tunnel.h"

#include "model/networking/messages/message.h"

#include "model/networking/utility/buffer-reader.h"
#include "model/networking/utility/buffer-writer.h"
#include "model/networking/utility/data.h"

using namespace model;

ClientTunnel::ClientTunnel(
    std::shared_ptr<Connection> connection,
    std::shared_ptr<event_base> base,
    const std::string& ip_address,
    const std::string& port) : Tunnel(TunnelType::Client, connection, base, ip_address, port) {}

int ClientTunnel::SendMessage(Message* message) {
    if (message->GetStreamType() != StreamType::ClientStreamOut) {
        // message must be a client stream out
        return -1;
    }

    std::string packet = message->Serialize();

    if (!packet.length()) {
        // packet is empty, failed to format message
        return -1;
    }

    // send packet
    return WriteBufferLine(bev, packet);
}
