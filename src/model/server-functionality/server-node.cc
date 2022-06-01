#include "server-node.h"

#include <string>

using namespace model_server_functionality;
using namespace std;

ServerNode::ServerNode(const string &uuid, const string &name, const string &owner, const std::string &ip, const std::string &port) {
  this->uuid = uuid;
  this->name = name;
  this->owner = owner;
  this->ip = ip;
  this->port = port;
}

string ServerNode::GetUuid() { return this->uuid; }

string ServerNode::GetName() { return this->name; }

string ServerNode::GetOwner() { return this->owner; }

string ServerNode::GetIp() { return this->ip; }

string ServerNode::GetPort() { return this->port; }