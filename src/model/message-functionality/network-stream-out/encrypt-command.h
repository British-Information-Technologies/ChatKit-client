#ifndef MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMOUT_ENCRYPTCOMMAND_H_
#define MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMOUT_ENCRYPTCOMMAND_H_

#include "../message.h"

namespace chat_client_model_message_functionality_network_stream_out {
class EncryptCommand : public chat_client_model_message_functionality::Message {
 private:
  std::string key;

 public:
  EncryptCommand(const std::string &key);

  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace chat_client_model_message_functionality_network_stream_out

#endif