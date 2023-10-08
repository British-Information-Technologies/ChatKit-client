#include <string>
#include <memory>
#include <event2/event.h>
#include "msd/channel.hpp"

#include "connection-factory.h"

#include "model/networking/connection/client-connection.h"
#include "model/networking/connection/server-connection.h"

#include "model/networking/utility/data.h"

std::shared_ptr<model::Connection> model::GetConnection(
    model::ConnectionType type,
    const std::string &uuid,
    std::shared_ptr<event_base> base,
    msd::channel<model::Data> &network_manager_chann,
    const std::string &ip_address,
    const std::string &port
) 
{
    if (type == model::ConnectionType::Client) {
        return model::ClientConnection::Create(uuid, base, network_manager_chann, ip_address, port);
    }

    return model::ServerConnection::Create(uuid, base, network_manager_chann, ip_address, port);
}