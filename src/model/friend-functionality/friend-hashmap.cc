#include "friend-hashmap.h"

#include <memory>
#include <string>

#include "friend-node.h"

using namespace model_friend_functionality;
using namespace std;

map<const string, shared_ptr<FriendNode>>::iterator FriendHashmap::GetBegin() {
  return friend_map.begin();
}

map<const string, shared_ptr<FriendNode>>::iterator FriendHashmap::GetEnd() {
  return friend_map.end();
}

bool FriendHashmap::AddFriend(FriendNode& friend_node) {
  pair<map<const string, shared_ptr<FriendNode>>::iterator, bool> ret;
  string uuid = friend_node.GetUuid();
  shared_ptr<FriendNode> friend_ptr = make_shared<FriendNode>(friend_node);

  ret = friend_map.insert(
      pair<const string, shared_ptr<FriendNode>>(uuid, friend_ptr));

  return ret.second;
}

bool FriendHashmap::DeleteFriend(const string& uuid) {
  return friend_map.erase(uuid);
}

shared_ptr<FriendNode> FriendHashmap::GetFriend(const string& uuid) const {
  return friend_map.at(uuid);
}