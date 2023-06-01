#ifndef MODEL_NETWORKING_NETWORK_MANAGER_H_
#define MODEL_NETWORKING_NETWORK_MANAGER_H_

#include <string>
#include <unordered_map>
#include <memory>
#include <event2/event.h>
#include <msd/channel.hpp>

#include "connection.h"
#include "connection-factory.h"
#include "messages/message.h"

#include "include/cpp-chat-client/thread.h"

namespace model {
  class NetworkManager: public Thread {
    private:
      struct event_base *connection_base;
      
      msd::channel<std::string> in_chann;

      std::unordered_map<int, std::shared_ptr<Connection>>
      connections;

      std::unique_ptr<ConnectionFactory> connection_factory;

    public:
      NetworkManager();
      ~NetworkManager();

      void Launch();

      std::unordered_map<int, std::shared_ptr<Connection>>
      GetConnections();

      void TryCreateConnection(const int &type,
                           const std::string &ip_address,
                           const std::string &port);

      int SendMessage(const int &id, Message *message);

    protected:
      void InternalThreadEntry();
  };
}  // namespace model_networking

#endif