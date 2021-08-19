#ifndef MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUT_ERRORMESSAGE_
#define MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUT_ERRORMESSAGE_

#include "../message.h"

namespace chat_client_model_message_functionality_client_stream_out {
class ErrorMessage : public chat_client_model_message_functionality::Message {
 public:
  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace chat_client_model_message_functionality_client_stream_out

#endif