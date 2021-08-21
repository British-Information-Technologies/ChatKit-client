#ifndef MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMOUTFACTORY_
#define MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMOUTFACTORY_

#include <memory>

#include "message.h"

namespace chat_client_model_message_functionality {
class NetworkStreamOutFactory {
 public:
  std::unique_ptr<Message> GetMessage();
};
}  // namespace chat_client_model_message_functionality

#endif