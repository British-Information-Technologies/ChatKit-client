#include <memory>
#include <string>

#include "data-model.h"

#include "friend-functionality/friend-utility.h"
#include "server-functionality/server-utility.h"

using namespace model;
using namespace model_friend_functionality;
using namespace model_server_functionality;

DataModel::DataModel(
  std::unique_ptr<model_friend_functionality::FriendAPI> friend_api,
  std::unique_ptr<model_server_functionality::ServerAPI> server_api
): friend_api(std::move(friend_api)), server_api(std::move(server_api))
{}

bool DataModel::AddFriend(const std::string &uuid, const std::string &name, const std::string &ip, const std::string &port) {
  return friend_api->AddFriend(uuid, name, ip, port);
}

bool DataModel::DeleteFriend(const std::string &uuid) {
  return friend_api->DeleteFriend(uuid);
}

std::shared_ptr<FriendNode> DataModel::GetFriend(const std::string &uuid) const {
  return friend_api->GetFriend(uuid);
}

bool DataModel::AddServer(const std::string &uuid, const std::string &name, const std::string &owner, const std::string &ip, const std::string &port) {
  return server_api->AddServer(uuid, name, owner, ip, port);
}

bool DataModel::DeleteServer(const std::string &uuid) {
  return server_api->DeleteServer(uuid);
}

std::shared_ptr<ServerNode> DataModel::GetServer(const std::string &uuid) const {
  return server_api->GetServer(uuid);
}