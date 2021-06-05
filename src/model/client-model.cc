#include "client-model.h"

using namespace chat_client_model;

bool ClientModel::AddFriend(FriendNode& friend_node) {
  if (prev.GetUuid() != friend_node.GetUuid()) {
    prev = friend_node;
    return true;
  }

  return false;
}