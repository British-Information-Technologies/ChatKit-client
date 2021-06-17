#ifndef CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDUTILITY_
#define CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDUTILITY_

#include <memory>
#include <string>

#include "friend-api.h"
#include "friend-node.h"

namespace chat_client_model_friend_functionality {
class FriendUtility : public FriendAPI {
 public:
  bool AddFriend(const std::string &);
  std::shared_ptr<FriendNode> GetFriend(const std::string &) const;
};
}  // namespace chat_client_model_friend_functionality

#endif