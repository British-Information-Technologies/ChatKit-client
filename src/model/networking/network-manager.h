#ifndef MODEL_NETWORKING_NETWORK_MANAGER_H_
#define MODEL_NETWORKING_NETWORK_MANAGER_H_

#include <string>
#include <unordered_map>
#include <memory>
#include <event2/event.h>
#include <nlohmann/json.hpp>
#include "msd/channel.hpp"

#include "connection.h"
#include "connection-factory.h"
#include "messages/message.h"

#include "../../../include/cpp-chat-client/thread.h"

using json = nlohmann::json;

namespace model {
  class NetworkManager: public include::Thread {
    private:
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

    protected:
      void InternalThreadEntry();

    private:
      void AnalyseIncomingMessage(int sockfd, Message *message);
  };
}  // namespace model_networking

#endif