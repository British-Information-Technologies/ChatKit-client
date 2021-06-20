#ifndef CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDLIST_
#define CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDLIST_

#include <memory>
#include <string>

#include "friend-node.h"

namespace chat_client_model_friend_functionality {

class FriendList {
 public:
  virtual bool AddFriend(FriendNode&) = 0;
  virtual bool DeleteFriend(const std::string&) = 0;
  virtual std::shared_ptr<FriendNode> GetFriend(const std::string&) const = 0;
};

}  // namespace chat_client_model_friend_functionality

#endif