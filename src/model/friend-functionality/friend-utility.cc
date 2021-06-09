#include "friend-utility.h"

using namespace chat_client_model_friend_functionality;

bool FriendUtility::AddFriend(FriendNode& friend_node) {
  if (prev.GetUuid() != friend_node.GetUuid()) {
    prev = friend_node;
    return true;
  }
  return false;
}