#ifndef CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDLIST_
#define CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDLIST_

#include <memory>
#include <string>

#include "friend-node.h"

using namespace std;

namespace chat_client_model_friend_functionality {

class FriendList {
 public:
  virtual bool AddFriend(FriendNode&) = 0;
  virtual shared_ptr<FriendNode> GetFriend(const string&) const = 0;
};

}  // namespace chat_client_model_friend_functionality

#endif