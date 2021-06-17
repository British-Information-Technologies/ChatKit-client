#ifndef CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDAPI_
#define CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDAPI_

#include <string>

#include "friend-hashmap.h"
#include "friend-list.h"

using namespace std;

namespace chat_client_model_friend_functionality {
class FriendAPI {
 public:
  virtual bool AddFriend(const string &) = 0;
  virtual shared_ptr<FriendNode> GetFriend(const string &) const = 0;

 protected:
  FriendList *friend_list = new FriendHashmap();
};
}  // namespace chat_client_model_friend_functionality

#endif