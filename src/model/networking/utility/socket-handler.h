#ifndef CPPCHATCLIENT_SOCKET_HANDLER_H_
#define CPPCHATCLIENT_SOCKET_HANDLER_H_

#include <string>

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

  virtual int send(secure_string &) = 0;
  virtual secure_string recv() = 0;
};
}  // namespace networking_utility

#endif