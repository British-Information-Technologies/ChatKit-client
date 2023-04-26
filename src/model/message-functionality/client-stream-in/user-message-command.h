#ifndef MODEL_MESSAGE_FUNCTIONALITY_CLIENT_STREAM_IN_USER_MESSAGE_COMMAND_H_
#define MODEL_MESSAGE_FUNCTIONALITY_CLIENT_STREAM_IN_USER_MESSAGE_COMMAND_H_

#include "cpp-chat-client/model/message-functionality/message.h"

namespace model_message_functionality_client_stream_in {
class UserMessageCommand : public model_message_functionality::Message {
 private:
  std::string from;
  std::string content;

 public:
  UserMessageCommand(const std::string &from, const std::string &content);

  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace model_message_functionality_client_stream_in

#endif