#ifndef MODEL_NETWORKING_NETWORK_MANAGER_H_
#define MODEL_NETWORKING_NETWORK_MANAGER_H_

#include <string>
#include <unordered_map>
#include <memory>

#include "connection.h"
#include "connection-factory.h"

namespace model {
  class NetworkManager {
    private:
      std::unordered_map<int, std::shared_ptr<Connection>>
      connections;

      std::unique_ptr<ConnectionFactory> connection_factory;

    public:
      NetworkManager();
      ~NetworkManager();

      std::unordered_map<int, std::shared_ptr<Connection>>
      GetConnections();

      void TryCreateConnection(const int &type,
                           const std::string &ip_address,
                           const std::string &port);

      int SendMessage(const int &id, std::string &message);

      
  };
}  // namespace model_networking

#endif