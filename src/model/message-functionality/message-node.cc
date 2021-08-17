#include "message-node.h"

using namespace std;
using namespace chat_client_model_message_functionality;

MessageNode::MessageNode(const string &content, const ClientStreamIn &type) {
  this->content = content;
  this->type = type;
}

string MessageNode::GetContent() { return this->content; }

ClientStreamIn MessageNode::GetType() { return this->type; }
