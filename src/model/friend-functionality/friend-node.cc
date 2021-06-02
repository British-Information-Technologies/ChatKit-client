#include "friend-node.h"

#include <string>

using namespace chat_client_model_friend_functionality;

FriendNode::FriendNode(std::string *name, std::string *uuid) {
  this->name = *name;
  this->uuid = *uuid;
}

std::string FriendNode::GetUuid() { return this->uuid; }

std::string FriendNode::GetName() { return this->name; }