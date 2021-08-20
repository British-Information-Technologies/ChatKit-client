#ifndef MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMIN_REQUESTCOMMAND_
#define MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMIN_REQUESTCOMMAND_

#include "../message.h"

namespace chat_client_model_message_functionality_network_stream_in {
class RequestCommand : public chat_client_model_message_functionality::Message {
 public:
  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace chat_client_model_message_functionality_network_stream_in

#endif