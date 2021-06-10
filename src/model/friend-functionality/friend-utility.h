#ifndef CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDUTILITY_
#define CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDUTILITY_

#include <memory>

#include "friend-api.h"
#include "friend-node.h"

using namespace std;
namespace chat_client_model_friend_functionality {
class FriendUtility : public FriendAPI {
 public:
  bool AddFriend(FriendNode &);
};
}  // namespace chat_client_model_friend_functionality

#endif