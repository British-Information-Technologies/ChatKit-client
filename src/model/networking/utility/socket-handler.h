#ifndef MODEL_NETWORKING_UTILITY_SOCKET_HANDLER_H_
#define MODEL_NETWORKING_UTILITY_SOCKET_HANDLER_H_

#include <string>

#include "../messages/message.h"

namespace model {
  class SocketHandler {
    public:
      virtual int Send(int sockfd, Message *message) = 0;
      virtual std::string Recv(int sockfd) = 0;
  };
}  // namespace model_networking_utility

#endif