#ifndef MODEL_MESSAGE_FUNCTIONALITY_NETWORK_STREAM_IN_GOT_INFO_COMMAND_H_
#define MODEL_MESSAGE_FUNCTIONALITY_NETWORK_STREAM_IN_GOT_INFO_COMMAND_H_

#include "../message.h"

namespace model_message_functionality_network_stream_in {
class GotInfoCommand : public model_message_functionality::Message {
 private:
  std::string server_name;
  std::string server_owner;

 public:
  GotInfoCommand(const std::string &server_name,
                 const std::string &server_owner);

  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace model_message_functionality_network_stream_in

#endif