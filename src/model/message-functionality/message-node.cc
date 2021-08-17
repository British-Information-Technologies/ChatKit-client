#include "message-node.h"

using namespace std;
using namespace chat_client_model_message_functionality;

MessageNode::MessageNode(const string &content) { this->content = content; }

string MessageNode::GetContent() { return this->content; }

ClientStreamIn MessageNode::GetType() { return ClientStreamIn::Connect; }
