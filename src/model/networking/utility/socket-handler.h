#ifndef CPPCHATCLIENT_SOCKET_HANDLER_H_
#define CPPCHATCLIENT_SOCKET_HANDLER_H_

#include <memory>
#include <string>

#include "../../message-functionality/message.h"
#include "buffer-reader.h"
#include "buffer-writer.h"
#include "memory-manager.h"

namespace networking_utility {
class SocketHandler {
 protected:
  BufferWriter *writer;
  BufferReader *reader;

 public:
  SocketHandler(int);
  ~SocketHandler();

  virtual int send(chat_client_model_message_functionality::Message *) = 0;
  virtual std::string recv() = 0;
};
}  // namespace networking_utility

#endif