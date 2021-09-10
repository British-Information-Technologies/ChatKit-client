#ifndef MODEL_NETWORK_SENDER_H_
#define MODEL_NETWORK_SENDER_H_

#include <string>
#include <unordered_map>

#include "connection.h"

namespace networking {

class NetworkSender {
 private:
  std::shared_ptr<
      std::unordered_map<int, std::shared_ptr<networking::Connection>>>
      connections;

 public:
  ~NetworkSender();

  std::shared_ptr<
      std::unordered_map<int, std::shared_ptr<networking::Connection>>>
  get_connections();

  void try_create_connection(const std::string &ip_address,
                             const std::string &port);

  int send_message(const int &id, std::string &message);
};

}  // namespace networking

#endif