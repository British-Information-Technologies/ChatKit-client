#include "friend-utility.h"

using namespace chat_client_model_friend_functionality;

bool FriendUtility::AddFriend(FriendNode& friend_node) {
  if (prev[0].GetUuid() != friend_node.GetUuid() &&
      prev[1].GetUuid() != friend_node.GetUuid()) {
    prev[pos % 2] = friend_node;
    ++pos;
    return true;
  }
  return false;
}