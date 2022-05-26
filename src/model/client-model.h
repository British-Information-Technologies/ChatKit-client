#ifndef MODEL_CLIENT_MODEL_H_
#define MODEL_CLIENT_MODEL_H_

#include <memory>
#include <string>

#include "friend-functionality/friend-api.h"
#include "friend-functionality/friend-node.h"
#include "server-functionality/server-api.h"
#include "server-functionality/server-node.h"
#include "networking/network-sender.h"

namespace model {
class ClientModel {
 private:
  std::shared_ptr<model_friend_functionality::FriendAPI> friend_api;
  std::shared_ptr<model_server_functionality::ServerAPI> server_api;

  std::shared_ptr<model_networking::NetworkSender> network_sender;

 public:
  ClientModel();

  bool AddFriend(const std::string &uuid, const std::string &name);

  bool DeleteFriend(const std::string &uuid);

  std::shared_ptr<model_friend_functionality::FriendNode> GetFriend(
      const std::string &uuid) const;

  bool AddServer(const std::string &uuid, const std::string &name, const std::string &owner, const std::string &ip, const std::string &port);

  bool DeleteServer(const std::string &uuid);

  std::shared_ptr<model_server_functionality::ServerNode> GetServer(
      const std::string &uuid) const;

  void StartReceiver();

  void StopReceiver();

  std::unordered_map<int, std::shared_ptr<model_networking::Connection>>
  LoadConnections();

  int SendMessage(const int &, std::string &);
};
}  // namespace model

#endif