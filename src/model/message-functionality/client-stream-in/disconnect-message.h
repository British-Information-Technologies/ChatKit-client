#ifndef MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMIN_DISCONNECTMESSAGE_
#define MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMIN_DISCONNECTMESSAGE_

#include "../message.h"

namespace chat_client_model_message_functionality_client_stream_in {
class DisconnectMessage
    : public chat_client_model_message_functionality::Message {
 public:
  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace chat_client_model_message_functionality_client_stream_in

#endif