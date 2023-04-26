#ifndef MODEL_NETWORK_SENDER_H_
#define MODEL_NETWORK_SENDER_H_

#include <string>
#include <unordered_map>

#include "connection.h"
#include "connection-factory.h"

namespace model_networking {

class NetworkSender {
 private:
  std::unordered_map<int, std::shared_ptr<model_networking::Connection>>
      connections;

  std::unique_ptr<ConnectionFactory> connection_factory;

 public:
  NetworkSender();
  ~NetworkSender();

  std::unordered_map<int, std::shared_ptr<model_networking::Connection>>
  GetConnections();

  void TryCreateConnection(const int &type,
                           const std::string &ip_address,
                           const std::string &port);

  int SendMessage(const int &id, std::string &message);
};

}  // namespace model_networking

#endif