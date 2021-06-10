#include "friend-utility.h"

#include <memory>

using namespace chat_client_model_friend_functionality;

using namespace std;

bool FriendUtility::AddFriend(FriendNode& friend_node) {
  return friend_list->AddFriend(friend_node);
}