#ifndef CPPCHATCLIENT_MODEL_MESSAGEFUNCTIONALITY_MESSAGENODE_
#define CPPCHATCLIENT_MODEL_MESSAGEFUNCTIONALITY_MESSAGENODE_

#include "client-stream-in.h"
#include "string"

namespace chat_client_model_message_functionality {
class MessageNode {
 private:
  std::string content;
  ClientStreamIn type;

 public:
  MessageNode(const std::string &content, const ClientStreamIn &type);

  std::string GetContent();

  ClientStreamIn GetType();
};
}  // namespace chat_client_model_message_functionality

#endif