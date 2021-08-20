#ifndef MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMOUT_CONNECTCOMMAND_
#define MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMOUT_CONNECTCOMMAND_

#include "../message.h"

namespace chat_client_model_message_functionality_network_stream_out {
class ConnectCommand : public chat_client_model_message_functionality::Message {
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
}  // namespace chat_client_model_message_functionality_network_stream_out

#endif