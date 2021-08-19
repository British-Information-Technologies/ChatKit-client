#ifndef MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUT_GLOBALMESSAGE_
#define MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUT_GLOBALMESSAGE_

#include "../message.h"

namespace chat_client_model_message_functionality_client_stream_out {
class GlobalMessage : public chat_client_model_message_functionality::Message {
 private:
  std::string content;

 public:
  GlobalMessage(const std::string &content);

  std::string ToString();

  nlohmann::json ToJson();
};
}  // namespace chat_client_model_message_functionality_client_stream_out

#endif