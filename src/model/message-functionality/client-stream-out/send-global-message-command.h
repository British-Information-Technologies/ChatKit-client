#ifndef MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUT_SENDGLOBALMESSAGECOMMAND_
#define MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUT_SENDGLOBALMESSAGECOMMAND_

#include "../message.h"

namespace chat_client_model_message_functionality_client_stream_out {
class SendGlobalMessageCommand
    : public chat_client_model_message_functionality::Message {
 private:
  std::string content;

 public:
  SendGlobalMessageCommand(const std::string &content);

  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace chat_client_model_message_functionality_client_stream_out

#endif