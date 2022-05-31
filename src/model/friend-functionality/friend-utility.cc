#include "friend-utility.h"

#include <memory>
#include <string>

#include "friend-node.h"

using namespace model_friend_functionality;
using namespace std;

map<const string, shared_ptr<FriendNode>>::iterator FriendUtility::Begin() {
  return friend_list->GetBegin();
}

map<const string, shared_ptr<FriendNode>>::iterator FriendUtility::End() {
  return friend_list->GetEnd();
}

bool FriendUtility::AddFriend(const string& uuid, const string& name, const string& ip, const string& port) {
  FriendNode friend_node(uuid, name, ip, port);
  return friend_list->AddFriend(friend_node);
}

bool FriendUtility::DeleteFriend(const string& uuid) {
  return friend_list->DeleteFriend(uuid);
}

shared_ptr<FriendNode> FriendUtility::GetFriend(const string& uuid) const {
  return friend_list->GetFriend(uuid);
}