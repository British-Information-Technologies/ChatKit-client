#ifndef MODEL_FRIEND_FUNCTIONALITY_FRIEND_UTILITY_H_
#define MODEL_FRIEND_FUNCTIONALITY_FRIEND_UTILITY_H_

#include <memory>
#include <string>

#include "friend-api.h"
#include "friend-node.h"

namespace model_friend_functionality {
class FriendUtility : public FriendAPI {
 public:
  bool AddFriend(const std::string &);
  bool DeleteFriend(const std::string &);
  std::shared_ptr<FriendNode> GetFriend(const std::string &) const;
};
}  // namespace model_friend_functionality

#endif