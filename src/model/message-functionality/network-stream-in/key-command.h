#ifndef MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMIN_KEYCOMMAND_H_
#define MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMIN_KEYCOMMAND_H_

#include "../message.h"

namespace chat_client_model_message_functionality_network_stream_in {
class KeyCommand : public chat_client_model_message_functionality::Message {
 private:
  std::string key;

 public:
  KeyCommand(const std::string &key);

  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace chat_client_model_message_functionality_network_stream_in

#endif