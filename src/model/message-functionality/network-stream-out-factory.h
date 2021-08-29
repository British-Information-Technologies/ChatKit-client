#ifndef MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMOUTFACTORY_
#define MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMOUTFACTORY_

#include "server-stream-out-factory.h"

namespace chat_client_model_message_functionality {
class NetworkStreamOutFactory : public ServerStreamOutFactory {
 public:
  std::unique_ptr<Message> GetMessage(const std::string &plaintext);
};
}  // namespace chat_client_model_message_functionality

#endif