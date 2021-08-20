#ifndef MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMIN_GOTINFOCOMMAND_
#define MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMIN_GOTINFOCOMMAND_

#include "../message.h"

namespace chat_client_model_message_functionality_network_stream_in {
class GotInfoCommand : public chat_client_model_message_functionality::Message {
 private:
  std::string server_name;
  std::string server_owner;

 public:
  GotInfoCommand(const std::string &server_name,
                 const std::string &server_owner);

  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace chat_client_model_message_functionality_network_stream_in

#endif