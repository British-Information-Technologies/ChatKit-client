#ifndef MODEL_MESSAGE_FUNCTIONALITY_CLIENT_STREAM_OUT_SEND_MESSAGE_COMMAND_H_
#define MODEL_MESSAGE_FUNCTIONALITY_CLIENT_STREAM_OUT_SEND_MESSAGE_COMMAND_H_

#include "cpp-chat-client/model/message-functionality/message.h"

namespace model_message_functionality_client_stream_out {
class SendMessageCommand : public model_message_functionality::Message {
 private:
  std::string to;
  std::string content;

 public:
  SendMessageCommand(const std::string &to, const std::string &content);

  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace model_message_functionality_client_stream_out

#endif