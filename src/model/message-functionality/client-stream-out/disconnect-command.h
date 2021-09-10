#ifndef MODEL_MESSAGE_FUNCTIONALITY_CLIENT_STREAM_OUT_DISCONNECT_COMMAND_H_
#define MODEL_MESSAGE_FUNCTIONALITY_CLIENT_STREAM_OUT_DISCONNECT_COMMAND_H_

#include "../message.h"

namespace model_message_functionality_client_stream_out {
class DisconnectCommand : public model_message_functionality::Message {
 public:
  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace model_message_functionality_client_stream_out

#endif