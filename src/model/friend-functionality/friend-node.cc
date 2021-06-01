#include "friend-node.h"

#include <string>

using namespace chat_client_model_friend_functionality;

FriendNode::FriendNode(std::string *name) { this->name = *name; }

std::string FriendNode::GetUuid() { return "testtesttest1234567890"; }

std::string FriendNode::GetName() { return this->name; }