#ifndef MODEL_NETWORKING_CONNECTION_FACTORY_H_
#define MODEL_NETWORKING_CONNECTION_FACTORY_H_

#include <memory>
#include <string>
#include <event2/event.h>
#include "msd/channel.hpp"

#include "connection.h"

namespace model {
    class ConnectionFactory {
        public:
            std::shared_ptr<Connection> GetConnection(
            const int &type, std::shared_ptr<struct event_base> base, msd::channel<std::string> &network_manager_chann, const std::string &ip_address, const std::string &port);
    };
}  // namespace model_networking

#endif