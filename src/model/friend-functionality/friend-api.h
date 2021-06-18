#ifndef CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDAPI_
#define CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDAPI_

#include <string>

#include "friend-hashmap.h"
#include "friend-list.h"

namespace chat_client_model_friend_functionality {
class FriendAPI {
 public:
  virtual bool AddFriend(const std::string &) = 0;
  virtual std::shared_ptr<FriendNode> GetFriend(const std::string &) const = 0;

 protected:
  FriendList *friend_list = new FriendHashmap();
};
}  // namespace chat_client_model_friend_functionality

#endif