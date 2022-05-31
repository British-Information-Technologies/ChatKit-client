#ifndef MODEL_FRIEND_FUNCTIONALITY_FRIEND_API_H_
#define MODEL_FRIEND_FUNCTIONALITY_FRIEND_API_H_

#include <memory>
#include <string>

#include "friend-list.h"
#include "friend-hashmap.h"


namespace model_friend_functionality {
class FriendAPI {
 public:

  FriendAPI() { friend_list = std::make_unique<FriendHashmap>(); }

  virtual std::map<const std::string, std::shared_ptr<FriendNode>>::iterator Begin() = 0;

  virtual std::map<const std::string, std::shared_ptr<FriendNode>>::iterator End() = 0;

  virtual bool AddFriend(const std::string &uuid, const std::string &name, const std::string& ip, const std::string& port) = 0;
 
  virtual bool DeleteFriend(const std::string &uuid) = 0;
 
  virtual std::shared_ptr<FriendNode> GetFriend(const std::string &uuid) const = 0;

 protected:
  std::unique_ptr<FriendList> friend_list;
};
}  // namespace model_friend_functionality

#endif