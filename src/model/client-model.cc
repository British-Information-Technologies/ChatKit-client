#include "client-model.h"

using namespace chat_client_model;

bool ClientModel::AddFriend(FriendNode& friend_node) {
  return friend_api->AddFriend(friend_node);
}