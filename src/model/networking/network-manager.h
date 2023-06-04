#ifndef MODEL_NETWORKING_NETWORK_MANAGER_H_
#define MODEL_NETWORKING_NETWORK_MANAGER_H_

#include <string>
#include <unordered_map>
#include <memory>
#include <event2/event.h>
#include <nlohmann/json.hpp>
#include <mutex>
#include "msd/channel.hpp"

#include "connection.h"
#include "connection-factory.h"
#include "messages/message.h"

using json = nlohmann::json;

namespace model {
  class NetworkManager {
    private:
      std::mutex connections_mutex;

      std::shared_ptr<struct event_base> connection_base;
      
      msd::channel<json> in_chann;

      std::unordered_map<int, std::shared_ptr<Connection>>
      connections;

    public:
      NetworkManager();
      ~NetworkManager();

      void Launch();

      int ConnectToServiceServer();

      int InitiateSecureConnection(const int &sockfd);

      int SendMessage(const int &id, std::string &data);
  };
}  // namespace model_networking

#endif