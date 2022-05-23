#ifndef MODEL_FRIEND_FUNCTIONALITY_FRIEND_LIST_H_
#define MODEL_FRIEND_FUNCTIONALITY_FRIEND_LIST_H_

#include <memory>
#include <string>

#include "friend-node.h"

namespace model_friend_functionality {

class FriendList {
 public:
  virtual bool AddFriend(FriendNode &friend_node) = 0;
  virtual bool DeleteFriend(const std::string &uuid) = 0;
  virtual std::shared_ptr<FriendNode> GetFriend(const std::string &uuid) const = 0;
};

}  // namespace model_friend_functionality

#endif