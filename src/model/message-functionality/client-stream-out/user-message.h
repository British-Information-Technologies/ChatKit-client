#ifndef MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUT_USERMESSAGE_
#define MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUT_USERMESSAGE_

#include "../message.h"

namespace chat_client_model_message_functionality_client_stream_out {
class UserMessage : public chat_client_model_message_functionality::Message {
 private:
  std::string from;
  std::string content;

 public:
  UserMessage(const std::string &from, const std::string &content);

  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace chat_client_model_message_functionality_client_stream_out

#endif