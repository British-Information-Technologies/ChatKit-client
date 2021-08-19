#ifndef MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUT_UPDATECOMMAND_
#define MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUT_UPDATECOMMAND_

#include "../message.h"

namespace chat_client_model_message_functionality_client_stream_out {
class UpdateCommand : public chat_client_model_message_functionality::Message {
 public:
  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace chat_client_model_message_functionality_client_stream_out

#endif