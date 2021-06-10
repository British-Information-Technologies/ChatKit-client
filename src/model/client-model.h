#ifndef CPPCHATCLIENT_MODEL_CLIENTMODEL_
#define CPPCHATCLIENT_MODEL_CLIENTMODEL_

#include "friend-functionality/friend-node.h"

using namespace chat_client_model_friend_functionality;

namespace chat_client_model {
class ClientModel {
 private:
  FriendNode prev[2];
  int pos = 0;

 public:
  bool AddFriend(FriendNode&);
};
}  // namespace chat_client_model

#endif