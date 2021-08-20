#ifndef MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMINFACTORY_
#define MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMINFACTORY_

#include <memory>

#include "message.h"

namespace chat_client_model_message_functionality {
class NetworkStreamInFactory {
 public:
  std::unique_ptr<Message> GetMessage(const std::string &plaintext);
};
}  // namespace chat_client_model_message_functionality

#endif