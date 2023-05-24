#ifndef MODEL_NETWORKING_CONNECTION_FACTORY_H_
#define MODEL_NETWORKING_CONNECTION_FACTORY_H_

#include <memory>
#include <string>

#include "connection.h"

namespace model {
    class ConnectionFactory {
        public:
            std::shared_ptr<Connection> GetConnection(
            const int &type, const std::string &ip_address, const std::string &port);
    };
}  // namespace model_networking

#endif