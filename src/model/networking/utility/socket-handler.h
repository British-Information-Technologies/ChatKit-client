#ifndef MODEL_NETWORKING_UTILITY_SOCKET_HANDLER_H_
#define MODEL_NETWORKING_UTILITY_SOCKET_HANDLER_H_

#include <memory>
#include <string>

#include "cpp-chat-client/model/message-functionality/message.h"
#include "buffer-writer.h"
#include "memory-manager.h"

namespace model_networking_utility {
class SocketHandler {
 protected:
  BufferWriter *writer;

 public:
  SocketHandler(int);
  ~SocketHandler();

  virtual int Send(model_message_functionality::Message *) = 0;
  virtual std::string Recv(std::string &payload) = 0;
};
}  // namespace model_networking_utility

#endif