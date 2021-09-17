#ifndef MODEL_NETWORK_SENDER_H_
#define MODEL_NETWORK_SENDER_H_

#include <string>
#include <unordered_map>

#include "connection.h"

namespace model_networking {

class NetworkSender {
 private:
  std::unordered_map<int, std::shared_ptr<model_networking::Connection>>
      connections;

 public:
  ~NetworkSender();

  std::unordered_map<int, std::shared_ptr<model_networking::Connection>>
  GetConnections();

  void TryCreateConnection(const std::string &ip_address,
                           const std::string &port);

  int SendMessage(const int &id, std::string &message);
};

}  // namespace model_networking

#endif