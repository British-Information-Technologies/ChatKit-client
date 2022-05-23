#ifndef MODEL_FRIEND_FUNCTIONALITY_FRIEND_API_H_
#define MODEL_FRIEND_FUNCTIONALITY_FRIEND_API_H_

#include <memory>
#include <string>

#include "friend-list.h"

namespace model_friend_functionality {
class FriendAPI {
 public:
  virtual bool AddFriend(const std::string &) = 0;
  virtual bool DeleteFriend(const std::string &) = 0;
  virtual std::shared_ptr<FriendNode> GetFriend(const std::string &) const = 0;

 protected:
  std::unique_ptr<FriendList> friend_list;

 public:
  FriendAPI();
};
}  // namespace model_friend_functionality

#endif