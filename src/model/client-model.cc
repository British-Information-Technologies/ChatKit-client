#include "client-model.h"

using namespace chat_client_model;

bool ClientModel::AddFriend(FriendNode& friend_node) {
  if (prev[0].GetUuid() != friend_node.GetUuid() &&
      prev[1].GetUuid() != friend_node.GetUuid()) {
    prev[pos % 2] = friend_node;
    ++pos;
    return true;
  }

  return false;
}