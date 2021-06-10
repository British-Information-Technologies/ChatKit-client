#ifndef CPPCHATCLIENT_MODEL_CLIENTMODEL_
#define CPPCHATCLIENT_MODEL_CLIENTMODEL_

#include "friend-functionality/friend-api.h"
#include "friend-functionality/friend-node.h"
#include "friend-functionality/friend-utility.h"

using namespace chat_client_model_friend_functionality;

namespace chat_client_model {
class ClientModel {
 private:
  FriendAPI *friend_api = new FriendUtility();

 public:
  bool AddFriend(FriendNode &);
  shared_ptr<FriendNode> GetFriend(const string &) const;
};
}  // namespace chat_client_model

#endif