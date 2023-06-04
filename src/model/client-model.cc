#include <memory>
#include <string>

#include "client-model.h"

#include "friend-functionality/friend-utility.h"
#include "server-functionality/server-utility.h"

#include "networking/network-manager.h"

using namespace model;
using namespace model_friend_functionality;
using namespace model_server_functionality;

ClientModel::ClientModel() {
  this->friend_api = std::make_shared<FriendUtility>();
  this->server_api = std::make_shared<ServerUtility>();
  this->network_manager = std::make_shared<NetworkManager>();
}

int ClientModel::Run() {
  if (network_manager->ConnectToServiceServer() != 0) {
    // failed to connect to service service
    return -1;
  }

  network_manager->Launch(); // blocks until application shutdowns

  return 0;
}

bool ClientModel::AddFriend(const std::string &uuid, const std::string &name, const std::string &ip, const std::string &port) {
  return friend_api->AddFriend(uuid, name, ip, port);
}

bool ClientModel::DeleteFriend(const std::string &uuid) {
  return friend_api->DeleteFriend(uuid);
}

std::shared_ptr<FriendNode> ClientModel::GetFriend(const std::string &uuid) const {
  return friend_api->GetFriend(uuid);
}

bool ClientModel::AddServer(const std::string &uuid, const std::string &name, const std::string &owner, const std::string &ip, const std::string &port) {
  return server_api->AddServer(uuid, name, owner, ip, port);
}

bool ClientModel::DeleteServer(const std::string &uuid) {
  return server_api->DeleteServer(uuid);
}

std::shared_ptr<ServerNode> ClientModel::GetServer(const std::string &uuid) const {
  return server_api->GetServer(uuid);
}

int ClientModel::SendMessage(const int& id, std::string& message) {
  return network_manager->SendMessage(id, message);
}