#include "client-model.h"

#include "networking/server/server-connection.h"

using namespace model;
using namespace model_friend_functionality;
using namespace model_networking;
using namespace std;

ClientModel::ClientModel() {
  this->friend_api = make_shared<FriendUtility>();
  this->network_sender = make_shared<NetworkSender>();
}

bool ClientModel::AddFriend(const string& uuid) {
  return friend_api->AddFriend(uuid);
}

bool ClientModel::DeleteFriend(const std::string& uuid) {
  return friend_api->DeleteFriend(uuid);
}

shared_ptr<FriendNode> ClientModel::GetFriend(const string& uuid) const {
  return friend_api->GetFriend(uuid);
}

std::shared_ptr<
    std::unordered_map<int, std::shared_ptr<model_networking::Connection>>>
ClientModel::LoadConnections() {
  /* Pesudo code
  nodes = get all connections from friend and server api

  for node in nodes:
    id = node.getid()
    ip = node.getip()
    port = node.getport()

    network_thread.try_create_connection(id, ip, port)

  return network_thread.get_connections()
  */

  // result above is faked until server api exists
  std::string server_ip = "localhost";
  std::string server_port = "3490";

  network_sender->TryCreateConnection(server_ip, server_port);

  return network_sender->GetConnections();
}

int ClientModel::SendMessage(const int& id, std::string& message) {
  return network_sender->SendMessage(id, message);
}