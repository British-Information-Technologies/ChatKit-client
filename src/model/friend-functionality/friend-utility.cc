#include "friend-utility.h"

#include <memory>
#include <string>

#include "friend-node.h"

using namespace chat_client_model_friend_functionality;
using namespace std;

bool FriendUtility::AddFriend(const string& uuid) {
  FriendNode friend_node(uuid, uuid);
  return friend_list->AddFriend(friend_node);
}

shared_ptr<FriendNode> FriendUtility::GetFriend(const string& uuid) const {
  return friend_list->GetFriend(uuid);
}