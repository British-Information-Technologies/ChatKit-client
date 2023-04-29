#ifndef MODEL_NETWORKING_UTILITY_SOCKET_HANDLER_H_
#define MODEL_NETWORKING_UTILITY_SOCKET_HANDLER_H_

#include <memory>
#include <string>

#include "../../message-functionality/message.h"
#include "buffer-writer.h"
#include "buffer-reader.h"

namespace model_networking_utility {
class SocketHandler {
 protected:
  BufferWriter *writer;
  BufferReader *reader;

 public:
  SocketHandler(int);
  ~SocketHandler();

  virtual int Send(model_message_functionality::Message *) = 0;
  virtual std::string Recv() = 0;
};
}  // namespace model_networking_utility

#endif