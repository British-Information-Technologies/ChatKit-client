#include <string>
#include <memory>
#include <event2/event.h>
#include <nlohmann/json.hpp>
#include "msd/channel.hpp"

#include "connection-factory.h"

#include "server-connection.h"

using json = nlohmann::json;

std::shared_ptr<model::Connection> model_connection_factory::GetConnection(
          std::shared_ptr<event_base> base, msd::channel<json> &network_manager_chann,
          const std::string &ip_address, const std::string &port) {
    return std::make_shared<model::ServerConnection>(base, network_manager_chann, ip_address, port);
}