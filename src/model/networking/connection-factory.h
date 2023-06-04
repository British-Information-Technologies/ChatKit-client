#ifndef MODEL_NETWORKING_CONNECTION_FACTORY_H_
#define MODEL_NETWORKING_CONNECTION_FACTORY_H_

#include <memory>
#include <string>
#include <event2/event.h>
#include <nlohmann/json.hpp>
#include "msd/channel.hpp"

#include "connection.h"

using json = nlohmann::json;

namespace model_connection_factory {
    std::shared_ptr<model::Connection> GetConnection(std::shared_ptr<struct event_base> base,
                                              msd::channel<json> &network_manager_chann,
                                              const std::string &ip_address,
                                              const std::string &port);
}  // namespace model_networking

#endif