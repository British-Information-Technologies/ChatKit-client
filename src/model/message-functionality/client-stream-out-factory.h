#ifndef MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUTFACTORY_
#define MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMOUTFACTORY_

#include <memory>

#include "message.h"

namespace chat_client_model_message_functionality {
class ClientStreamOutFactory {
 public:
  std::unique_ptr<Message> GetMessage();
};
}  // namespace chat_client_model_message_functionality

#endif