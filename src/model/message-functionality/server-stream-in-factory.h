#ifndef MODEL_MESSAGEFUNCTIONALITY_SERVER_STREAM_IN_FACTORY_H_
#define MODEL_MESSAGEFUNCTIONALITY_SERVER_STREAM_IN_FACTORY_H_

#include <memory>

#include "message.h"

namespace chat_client_model_message_functionality {

class ServerStreamInFactory {
 public:
  virtual std::unique_ptr<Message> GetMessage(const std::string &plaintext) = 0;
};

}  // namespace chat_client_model_message_functionality

#endif