#ifndef CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDHASHMAP_
#define CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDHASHMAP_

#include <map>
#include <memory>
#include <string>

#include "friend-list.h"
#include "friend-node.h"

namespace chat_client_model_friend_functionality {
class FriendHashmap : public FriendList {
 private:
  std::map<const std::string, std::shared_ptr<FriendNode>> friend_map;

 public:
  bool AddFriend(FriendNode&);

  bool DeleteFriend(const std::string&);

  std::shared_ptr<FriendNode> GetFriend(const std::string&) const;
};
}  // namespace chat_client_model_friend_functionality

#endif