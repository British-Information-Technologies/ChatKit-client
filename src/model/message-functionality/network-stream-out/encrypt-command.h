#ifndef MODEL_MESSAGE_FUNCTIONALITY_NETWORK_STREAM_OUT_ENCRYPT_COMMAND_H_
#define MODEL_MESSAGE_FUNCTIONALITY_NETWORK_STREAM_OUT_ENCRYPT_COMMAND_H_

#include "cpp-chat-client/model/message-functionality/message.h"

namespace model_message_functionality_network_stream_out {
class EncryptCommand : public model_message_functionality::Message {
 private:
  std::string key;

 public:
  EncryptCommand(const std::string &key);

  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace model_message_functionality_network_stream_out

#endif