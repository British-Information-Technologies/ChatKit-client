#include "friend-hashmap.h"

#include "friend-node.h"

using namespace chat_client_model_friend_functionality;
using namespace std;

bool FriendHashmap::AddFriend(FriendNode friend_node) {
  pair<map<string, FriendNode>::iterator, bool> ret;
  string uuid = friend_node.GetUuid();

  ret = friend_map.insert(pair<string, FriendNode>(uuid, friend_node));

  return ret.second;
}

FriendNode* FriendHashmap::GetFriend(const string* uuid) const {
  string name = "mitch";
  string uuid_one = "test";
  return (new FriendNode(&name, &uuid_one));
}