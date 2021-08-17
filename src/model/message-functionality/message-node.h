#ifndef CPPCHATCLIENT_MODEL_MESSAGEFUNCTIONALITY_MESSAGENODE_
#define CPPCHATCLIENT_MODEL_MESSAGEFUNCTIONALITY_MESSAGENODE_

#include "client-stream-in.h"
#include "string"

namespace chat_client_model_message_functionality {
class MessageNode {
 private:
  std::string content;

 public:
  MessageNode(const std::string &content);

  std::string GetContent();

  ClientStreamIn GetType();
};
}  // namespace chat_client_model_message_functionality

#endif