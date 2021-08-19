#ifndef MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMIN_ERRORCOMMAND_
#define MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMIN_ERRORCOMMAND_

#include "../message.h"

namespace chat_client_model_message_functionality_client_stream_in {
class ErrorCommand : public chat_client_model_message_functionality::Message {
 public:
  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace chat_client_model_message_functionality_client_stream_in

#endif