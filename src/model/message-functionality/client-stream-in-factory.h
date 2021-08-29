#ifndef MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMINFACTORY_
#define MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMINFACTORY_

#include "server-stream-in-factory.h"

namespace chat_client_model_message_functionality {
class ClientStreamInFactory : public ServerStreamInFactory {
 public:
  std::unique_ptr<Message> GetMessage(const std::string &plaintext);
};
}  // namespace chat_client_model_message_functionality

#endif