#ifndef MODEL_MESSAGE_FUNCTIONALITY_NETWORK_STREAM_OUT_CONNECT_COMMAND_H_
#define MODEL_MESSAGE_FUNCTIONALITY_NETWORK_STREAM_OUT_CONNECT_COMMAND_H_

#include "../message.h"

namespace model_message_functionality_network_stream_out {
class ConnectCommand : public model_message_functionality::Message {
 private:
  std::string uuid;
  std::string username;
  std::string address;

 public:
  ConnectCommand(const std::string &uuid, const std::string &username,
                 const std::string &address);

  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace model_message_functionality_network_stream_out

#endif