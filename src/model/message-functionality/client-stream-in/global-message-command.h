#ifndef MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMIN_GLOBALMESSAGECOMMAND_
#define MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMIN_GLOBALMESSAGECOMMAND_

#include "../message.h"

namespace chat_client_model_message_functionality_client_stream_in {
class GlobalMessageCommand
    : public chat_client_model_message_functionality::Message {
 private:
  std::string content;

 public:
  GlobalMessageCommand(const std::string &content);

  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace chat_client_model_message_functionality_client_stream_in

#endif