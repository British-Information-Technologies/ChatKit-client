#ifndef CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDHASHMAP_
#define CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDHASHMAP_

#include <map>
#include <string>

#include "friend-node.h"

namespace chat_client_model_friend_functionality {
class FriendHashmap {
 private:
  std::map<std::string, FriendNode> friend_map;

 public:
  bool AddFriend(FriendNode);

  FriendNode* GetFriend(const std::string*) const;
};
}  // namespace chat_client_model_friend_functionality

#endif