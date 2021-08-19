#ifndef MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUT_SENDMESSAGECOMMAND_
#define MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUT_SENDMESSAGECOMMAND_

#include "../message.h"

namespace chat_client_model_message_functionality_client_stream_out {
class SendMessageCommand
    : public chat_client_model_message_functionality::Message {
 private:
  std::string to;
  std::string content;

 public:
  SendMessageCommand(const std::string &to, const std::string &content);

  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace chat_client_model_message_functionality_client_stream_out

#endif