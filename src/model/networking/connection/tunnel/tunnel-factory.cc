#include <string>
#include <memory>
#include <event2/event.h>
#include "msd/channel.hpp"

#include "tunnel-factory.h"

#include "model/networking/connection/tunnel/tunnel.h"
#include "model/networking/connection/tunnel/client-tunnel.h"
#include "model/networking/connection/tunnel/server-tunnel.h"

std::unique_ptr<model::Tunnel> model::GetTunnel(
    model::TunnelType type,
    std::shared_ptr<Connection> connection,
    const std::string &uuid,
    std::shared_ptr<event_base> base,
    const std::string &ip_address,
    const std::string &port
) 
{
    if (type == model::TunnelType::Client) {
        return model::ClientTunnel::Create(connection, uuid, base, ip_address, port);
    }

    return model::ServerTunnel::Create(connection, uuid, base, ip_address, port);
}