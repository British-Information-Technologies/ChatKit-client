#include "msd/channel.hpp"
#include <event2/event.h>
#include <memory>
#include <string>

#include "tunnel-factory.h"

#include "model/networking/connection/tunnel/client-tunnel.h"
#include "model/networking/connection/tunnel/server-tunnel.h"
#include "model/networking/connection/tunnel/tunnel.h"

std::unique_ptr<model::Tunnel> model::GetTunnel(
    model::TunnelType type,
    std::shared_ptr<Connection> connection,
    std::shared_ptr<event_base> base,
    const std::string& ip_address,
    const std::string& port) {
    if (type == model::TunnelType::Client) {
        return std::make_unique<ClientTunnel>(
            connection,
            base,
            ip_address,
            port);
    }

    return std::make_unique<ServerTunnel>(
        connection,
        base,
        ip_address,
        port);
}