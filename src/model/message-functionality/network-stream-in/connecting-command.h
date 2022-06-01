#ifndef MODEL_MESSAGE_FUNCTIONALITY_NETWORK_STREAM_IN_CONNECTING_COMMAND_H_
#define MODEL_MESSAGE_FUNCTIONALITY_NETWORK_STREAM_IN_CONNECTING_COMMAND_H_

#include "../message.h"

namespace model_message_functionality_network_stream_in {
class ConnectingCommand : public model_message_functionality::Message {
 public:
  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace model_message_functionality_network_stream_in

#endif