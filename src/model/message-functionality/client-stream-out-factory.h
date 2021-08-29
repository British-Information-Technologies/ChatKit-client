#ifndef MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUTFACTORY_
#define MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUTFACTORY_

#include "server-stream-out-factory.h"

namespace chat_client_model_message_functionality {
class ClientStreamOutFactory : public ServerStreamOutFactory {
 public:
  std::unique_ptr<Message> GetMessage(const std::string &plaintext);
};
}  // namespace chat_client_model_message_functionality

#endif