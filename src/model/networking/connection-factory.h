#ifndef MODEL_NETWORKING_CONNECTION_FACTORY_H_
#define MODEL_NETWORKING_CONNECTION_FACTORY_H_

#include <memory>
#include <string>

#include "cpp-chat-client/model/networking/connection.h"

namespace model_networking {
class ConnectionFactory {
 public:
  std::shared_ptr<model_networking::Connection> GetConnection(
      const int &type, const std::string &ip_address, const std::string &port);
};
}  // namespace model_networking

#endif