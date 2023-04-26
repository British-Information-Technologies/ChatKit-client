#ifndef MODEL_MESSAGE_FUNCTIONALITY_SERVER_STREAM_OUT_FACTORY_H_
#define MODEL_MESSAGE_FUNCTIONALITY_SERVER_STREAM_OUT_FACTORY_H_

#include <memory>

#include "cpp-chat-client/model/message-functionality/message.h"

namespace model_message_functionality {

class ServerStreamOutFactory {
 public:
  virtual std::unique_ptr<Message> GetMessage(const std::string &plaintext) = 0;
};

}  // namespace model_message_functionality

#endif