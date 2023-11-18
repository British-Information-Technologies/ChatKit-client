#ifndef MODEL_NETWORKING_NETWORK_MANAGER_H_
#define MODEL_NETWORKING_NETWORK_MANAGER_H_

#include <string>
#include <unordered_map>
#include <memory>
#include <event2/event.h>
#include <mutex>
#include <thread>
#include "msd/channel.hpp"

#include "model/networking/connection/connection.h"
#include "messages/message.h"
#include "utility/data.h"

namespace model {
  class NetworkManager {
    private:
      std::mutex connections_mutex;

      std::unique_ptr<std::jthread> connection_base_thread;
      std::unique_ptr<std::jthread> channel_thread;

      std::shared_ptr<struct event_base> connection_base;
      
      msd::channel<Data> in_chann{};

      std::unordered_map<std::string, std::shared_ptr<Connection>> connections;
      

    public:
      NetworkManager();
      ~NetworkManager();

      void LaunchConnectionBase();

      void LaunchInputChannel();

      int LaunchListener(const std::string &uuid);

      int InitiateSecureConnection(const std::string &end_point_uuid, const std::string &service_uuid);

      int CreateConnection(
        const ConnectionType type,
        const std::string &uuid,
        const std::string &ip_address,
        const std::string &port
      );

      int SendMessage(const std::string &uuid, std::string &data);
      
      int SendClientMessage(
        const std::string &uuid,
        const std::string &time,
        const std::string &date,
        const std::string &data
      );
  };
}  // namespace model_networking

#endif