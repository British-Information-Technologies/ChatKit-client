#ifndef MODEL_NETWORKING_CONNECTION_FACTORY_H_
#define MODEL_NETWORKING_CONNECTION_FACTORY_H_

#include "msd/channel.hpp"
#include <event2/event.h>
#include <memory>
#include <string>

#include "connection.h"

#include "utility/data.h"

namespace model {
enum class ConnectionType {
    Client,
    Server,
};

std::shared_ptr<model::Connection> GetConnection(
    ConnectionType type,
    const std::string& uuid,
    std::shared_ptr<struct event_base> base,
    msd::channel<model::Data>& network_manager_chann,
    const std::string& ip_address,
    const std::string& port);
}// namespace model

#endif