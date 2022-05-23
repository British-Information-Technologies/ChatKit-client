#include "friend-node.h"

#include <string>

using namespace model_friend_functionality;
using namespace std;

FriendNode::FriendNode(const string &uuid, const string &name) {
  this->uuid = uuid;
  this->name = name;
}

string FriendNode::GetUuid() { return this->uuid; }

string FriendNode::GetName() { return this->name; }