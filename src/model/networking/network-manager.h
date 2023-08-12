#ifndef MODEL_NETWORKING_NETWORK_MANAGER_H_
#define MODEL_NETWORKING_NETWORK_MANAGER_H_

#include <string>
#include <unordered_map>
#include <memory>
#include <event2/event.h>
#include <mutex>
#include "msd/channel.hpp"

#include "connection.h"
#include "connection-factory.h"
#include "messages/message.h"
#include "utility/data.h"

namespace model {
  class NetworkManager {
    private:
      std::mutex connections_mutex;

      std::shared_ptr<struct event_base> connection_base;
      
      msd::channel<std::shared_ptr<Data>> in_chann;

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