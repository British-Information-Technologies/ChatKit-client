#include "friend-utility.h"

#include <memory>
#include <string>

#include "friend-node.h"

using namespace model_friend_functionality;
using namespace std;

bool FriendUtility::AddFriend(const string& uuid, const string& name) {
  FriendNode friend_node(uuid, name);
  return friend_list->AddFriend(friend_node);
}

bool FriendUtility::DeleteFriend(const string& uuid) {
  return friend_list->DeleteFriend(uuid);
}

shared_ptr<FriendNode> FriendUtility::GetFriend(const string& uuid) const {
  return friend_list->GetFriend(uuid);
}