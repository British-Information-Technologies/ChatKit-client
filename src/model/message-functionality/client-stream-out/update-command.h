#ifndef MODEL_MESSAGE_FUNCTIONALITY_CLIENT_STREAM_OUT_UPDATE_COMMAND_H_
#define MODEL_MESSAGE_FUNCTIONALITY_CLIENT_STREAM_OUT_UPDATE_COMMAND_H_

#include "cpp-chat-client/model/message-functionality/message.h"

namespace model_message_functionality_client_stream_out {
class UpdateCommand : public model_message_functionality::Message {
 public:
  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace model_message_functionality_client_stream_out

#endif