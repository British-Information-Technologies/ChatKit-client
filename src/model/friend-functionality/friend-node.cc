#include "friend-node.h"

#include <string>

using namespace model_friend_functionality;
using namespace std;

FriendNode::FriendNode(const string& uuid, const string& name, const string& ip, const string& port) {
    this->uuid = uuid;
    this->name = name;
    this->ip = ip;
    this->port = port;
}

string FriendNode::GetUuid() { return this->uuid; }

string FriendNode::GetName() { return this->name; }

string FriendNode::GetIp() { return this->ip; }

string FriendNode::GetPort() { return this->port; }