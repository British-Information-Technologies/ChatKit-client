#include "friend-hashmap.h"

#include "friend-node.h"

using namespace chat_client_model_friend_functionality;

bool FriendHashmap::AddFriend(FriendNode friend_node) {
  bool result = (this->prev.GetUuid().compare(friend_node.GetUuid()) != 0);
  this->prev = friend_node;
  return result;
}