#ifndef MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUT_DISCONNECTEDMESSAGE_
#define MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUT_DISCONNECTEDMESSAGE_

#include "../message.h"

namespace chat_client_model_message_functionality_client_stream_out {
class DisconnectedMessage
    : public chat_client_model_message_functionality::Message {
 public:
  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace chat_client_model_message_functionality_client_stream_out

#endif