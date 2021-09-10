#ifndef MODEL_MESSAGE_FUNCTIONALITY_NETWORK_STREAM_IN_FACTORY_H_
#define MODEL_MESSAGE_FUNCTIONALITY_NETWORK_STREAM_IN_FACTORY_H_

#include "server-stream-in-factory.h"

namespace model_message_functionality {
class NetworkStreamInFactory : public ServerStreamInFactory {
 public:
  std::unique_ptr<Message> GetMessage(const std::string &plaintext);
};
}  // namespace model_message_functionality

#endif