#ifndef CPPCHATCLIENT_MODEL_CLIENTMODEL_
#define CPPCHATCLIENT_MODEL_CLIENTMODEL_

#include <memory>
#include <string>

#include "friend-functionality/friend-api.h"
#include "friend-functionality/friend-node.h"
#include "friend-functionality/friend-utility.h"
#include "networking/network-sender.h"

namespace chat_client_model {
class ClientModel {
 private:
  std::shared_ptr<chat_client_model_friend_functionality::FriendAPI> friend_api;
  std::shared_ptr<networking::NetworkSender> network_sender;

 public:
  ClientModel();

  bool AddFriend(const std::string &);

  bool DeleteFriend(const std::string &);

  std::shared_ptr<chat_client_model_friend_functionality::FriendNode> GetFriend(
      const std::string &) const;

  void start_receiver();

  void stop_receiver();

  std::shared_ptr<
      std::unordered_map<int, std::shared_ptr<networking::Connection>>>
  load_connections();

  int send_message(const int &, std::string &);
};
}  // namespace chat_client_model

#endif