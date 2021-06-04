#include "friend-hashmap.h"

#include "friend-node.h"

using namespace chat_client_model_friend_functionality;

bool FriendHashmap::AddFriend(FriendNode friend_node) {
  if (friend_node.GetUuid() != prev[0].GetUuid() &&
      friend_node.GetUuid() != prev[1].GetUuid()) {
    prev[pos % 2] = friend_node;
    ++pos;
    return true;
  }

  return false;
}