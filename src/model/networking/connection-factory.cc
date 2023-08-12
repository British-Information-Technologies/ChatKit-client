#include <string>
#include <memory>
#include <event2/event.h>
#include "msd/channel.hpp"

#include "connection-factory.h"

#include "server-connection.h"

#include "utility/data.h"

std::shared_ptr<model::Connection> model_connection_factory::GetConnection(
    std::shared_ptr<event_base> base,
    msd::channel<std::shared_ptr<model::Data>> &network_manager_chann,
    const std::string &ip_address,
    const std::string &port
) 
{
    return std::make_shared<model::ServerConnection>(base, network_manager_chann, ip_address, port);
}