#ifndef MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMOUTFACTORY_
#define MODEL_MESSAGEFUNCTIONALITY_NETWORKSTREAMOUTFACTORY_

#include <memory>

#include "message.h"

namespace chat_client_model_message_functionality {
class NetworkStreamOutFactory {
 public:
  std::unique_ptr<Message> GetMessage(const std::string &uuid,
                                      const std::string &username,
                                      const std::string &address);
};
}  // namespace chat_client_model_message_functionality

#endif