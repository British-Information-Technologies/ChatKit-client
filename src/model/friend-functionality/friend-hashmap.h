#ifndef MODEL_FRIEND_FUNCTIONALITY_FRIEND_HASHMAP_H_
#define MODEL_FRIEND_FUNCTIONALITY_FRIEND_HASHMAP_H_

#include <map>
#include <memory>
#include <string>

#include "friend-list.h"
#include "friend-node.h"

namespace model_friend_functionality {
class FriendHashmap : public FriendList {
 private:
  std::map<const std::string, std::shared_ptr<FriendNode>> friend_map;

 public:
  bool AddFriend(FriendNode&);

  bool DeleteFriend(const std::string&);

  std::shared_ptr<FriendNode> GetFriend(const std::string&) const;
};
}  // namespace model_friend_functionality

#endif