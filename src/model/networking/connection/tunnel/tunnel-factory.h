#ifndef MODEL_NETWORKING_CONNECTION_TUNNEL_FACTORY_H_
#define MODEL_NETWORKING_CONNECTION_TUNNEL_FACTORY_H_

#include "msd/channel.hpp"
#include <event2/event.h>
#include <memory>
#include <string>

#include "model/networking/connection/tunnel/tunnel.h"

namespace model {
std::unique_ptr<model::Tunnel> GetTunnel(
    TunnelType type,
    std::shared_ptr<Connection> connection,
    std::shared_ptr<struct event_base> base,
    const std::string& ip_address,
    const std::string& port);
} // namespace model

#endif