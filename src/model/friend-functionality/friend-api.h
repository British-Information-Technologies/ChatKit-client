#ifndef CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDAPI_
#define CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDAPI_

#include "friend-list.h"

namespace chat_client_model_friend_functionality {
class FriendAPI {
 private:
  FriendList friend_list;

 public:
  virtual bool AddFriend(FriendNode&) = 0;
  virtual shared_ptr<FriendNode> GetFriend(const string&) const = 0;
};
}  // namespace chat_client_model_friend_functionality

#endif