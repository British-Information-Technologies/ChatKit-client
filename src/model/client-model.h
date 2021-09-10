#ifndef MODEL_CLIENT_MODEL_H_
#define MODEL_CLIENT_MODEL_H_

#include <memory>
#include <string>

#include "friend-functionality/friend-api.h"
#include "friend-functionality/friend-node.h"
#include "friend-functionality/friend-utility.h"
#include "networking/network-sender.h"

namespace model {
class ClientModel {
 private:
  std::shared_ptr<model_friend_functionality::FriendAPI> friend_api;
  std::shared_ptr<model_networking::NetworkSender> network_sender;

 public:
  ClientModel();

  bool AddFriend(const std::string &);

  bool DeleteFriend(const std::string &);

  std::shared_ptr<model_friend_functionality::FriendNode> GetFriend(
      const std::string &) const;

  void StartReceiver();

  void StopReceiver();

  std::shared_ptr<
      std::unordered_map<int, std::shared_ptr<model_networking::Connection>>>
  LoadConnections();

  int SendMessage(const int &, std::string &);
};
}  // namespace model

#endif