#ifndef MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMOUT_INFOCOMMAND_
#define MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMOUT_INFOCOMMAND_

#include "../message.h"

namespace chat_client_model_message_functionality_network_stream_out {
class InfoCommand : public chat_client_model_message_functionality::Message {
 public:
  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace chat_client_model_message_functionality_network_stream_out

#endif