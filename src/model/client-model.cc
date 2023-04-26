#include "cpp-chat-client/model/client-model.h"

#include "networking/server/server-connection.h"
#include "friend-functionality/friend-utility.h"
#include "server-functionality/server-utility.h"


using namespace model;
using namespace model_friend_functionality;
using namespace model_server_functionality;
using namespace model_networking;
using namespace std;

ClientModel::ClientModel() {
  this->friend_api = make_shared<FriendUtility>();
  this->server_api = make_shared<ServerUtility>();
  this->network_sender = make_shared<NetworkSender>();
}

bool ClientModel::AddFriend(const string &uuid, const string &name, const std::string &ip, const std::string &port) {
  return friend_api->AddFriend(uuid, name, ip, port);
}

bool ClientModel::DeleteFriend(const std::string &uuid) {
  return friend_api->DeleteFriend(uuid);
}

shared_ptr<FriendNode> ClientModel::GetFriend(const string &uuid) const {
  return friend_api->GetFriend(uuid);
}

bool ClientModel::AddServer(const string &uuid, const string &name, const string &owner, const std::string &ip, const std::string &port) {
  return server_api->AddServer(uuid, name, owner, ip, port);
}

bool ClientModel::DeleteServer(const std::string &uuid) {
  return server_api->DeleteServer(uuid);
}

shared_ptr<ServerNode> ClientModel::GetServer(const string &uuid) const {
  return server_api->GetServer(uuid);
}

std::unordered_map<int, std::shared_ptr<model_networking::Connection>>
ClientModel::LoadConnections() {
  int id = 0;

  for(auto it = server_api->Begin(); it != server_api->End(); ++it) {
    string server_ip = it->second->GetIp();
    string server_port = it->second->GetPort();

    network_sender->TryCreateConnection(id, server_ip, server_port);
  }

  id = 1;

  for(auto it = friend_api->Begin(); it != friend_api->End(); ++it) {
    string friend_ip = it->second->GetIp();
    string friend_port = it->second->GetPort();

    network_sender->TryCreateConnection(id, friend_ip, friend_port);
  }

  return network_sender->GetConnections();
}

int ClientModel::SendMessage(const int& id, std::string& message) {
  return network_sender->SendMessage(id, message);
}