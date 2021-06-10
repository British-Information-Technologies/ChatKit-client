#include "friend-utility.h"

#include <memory>
#include <string>

#include "friend-node.h"

using namespace chat_client_model_friend_functionality;

using namespace std;

bool FriendUtility::AddFriend(FriendNode& friend_node) {
  return friend_list->AddFriend(friend_node);
}

shared_ptr<FriendNode> FriendUtility::GetFriend(const string& uuid) const {
  string name = "test";
  FriendNode friend_node(&name, &name);
  shared_ptr<FriendNode> tmp = make_shared<FriendNode>(friend_node);
  return tmp;
}