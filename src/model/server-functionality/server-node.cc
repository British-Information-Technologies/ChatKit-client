#include "server-node.h"

#include <string>

using namespace model_server_functionality;
using namespace std;

ServerNode::ServerNode(const string &uuid, const string &name, const string &owner) {
  this->uuid = uuid;
  this->name = name;
  this->owner = owner;
}

string ServerNode::GetUuid() { return this->uuid; }

string ServerNode::GetName() { return this->name; }

string ServerNode::GetOwner() { return this->owner; }