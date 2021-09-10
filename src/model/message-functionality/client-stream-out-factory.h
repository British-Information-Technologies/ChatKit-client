#ifndef MODEL_MESSAGE_FUNCTIONALITY_CLIENT_STREAM_OUT_FACTORY_H_
#define MODEL_MESSAGE_FUNCTIONALITY_CLIENT_STREAM_OUT_FACTORY_H_

#include "server-stream-out-factory.h"

namespace model_message_functionality {
class ClientStreamOutFactory : public ServerStreamOutFactory {
 public:
  std::unique_ptr<Message> GetMessage(const std::string &plaintext);
};
}  // namespace model_message_functionality

#endif