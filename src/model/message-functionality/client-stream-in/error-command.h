#ifndef MODEL_MESSAGE_FUNCTIONALITY_CLIENT_STREAM_IN_ERROR_COMMAND_H_
#define MODEL_MESSAGE_FUNCTIONALITY_CLIENT_STREAM_IN_ERROR_COMMAND_H_

#include "cpp-chat-client/model/message-functionality/message.h"

namespace model_message_functionality_client_stream_in {
class ErrorCommand : public model_message_functionality::Message {
 public:
  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace model_message_functionality_client_stream_in

#endif