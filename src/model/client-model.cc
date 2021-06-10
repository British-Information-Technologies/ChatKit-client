#include "client-model.h"

using namespace chat_client_model;

bool ClientModel::AddFriend(FriendNode& friend_node) {
  return friend_api->AddFriend(friend_node);
}

shared_ptr<FriendNode> ClientModel::GetFriend(const string& uuid) const {
  string name = "test";
  FriendNode friend_node(&name, &name);
  shared_ptr<FriendNode> tmp = make_shared<FriendNode>(friend_node);
  return tmp;
}
