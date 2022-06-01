#ifndef MODEL_MESSAGE_FUNCTIONALITY_CLIENT_STREAM_IN_FACTORY_H_
#define MODEL_MESSAGE_FUNCTIONALITY_CLIENT_STREAM_IN_FACTORY_H_

#include "server-stream-in-factory.h"

namespace model_message_functionality {
class ClientStreamInFactory : public ServerStreamInFactory {
 public:
  std::unique_ptr<Message> GetMessage(const std::string &plaintext);
};
}  // namespace model_message_functionality

#endif