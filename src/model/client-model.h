#ifndef CPPCHATCLIENT_MODEL_CLIENTMODEL_
#define CPPCHATCLIENT_MODEL_CLIENTMODEL_

#include <memory>
#include <string>

#include "friend-functionality/friend-api.h"
#include "friend-functionality/friend-node.h"
#include "friend-functionality/friend-utility.h"

using namespace chat_client_model_friend_functionality;

namespace chat_client_model {
class ClientModel {
 private:
  FriendAPI *friend_api = new FriendUtility();

 public:
  bool AddFriend(const std::string &);
  bool DeleteFriend(const std::string &);
  std::shared_ptr<FriendNode> GetFriend(const std::string &) const;
};
}  // namespace chat_client_model

#endif