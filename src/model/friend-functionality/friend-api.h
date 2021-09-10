#ifndef MODEL_FRIEND_FUNCTIONALITY_FRIEND_API_H_
#define MODEL_FRIEND_FUNCTIONALITY_FRIEND_API_H_

#include <string>

#include "friend-hashmap.h"
#include "friend-list.h"

namespace model_friend_functionality {
class FriendAPI {
 public:
  virtual bool AddFriend(const std::string &) = 0;
  virtual bool DeleteFriend(const std::string &) = 0;
  virtual std::shared_ptr<FriendNode> GetFriend(const std::string &) const = 0;

 protected:
  FriendList *friend_list = new FriendHashmap();
};
}  // namespace model_friend_functionality

#endif