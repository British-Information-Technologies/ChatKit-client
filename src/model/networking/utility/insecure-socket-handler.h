#ifndef MODEL_NETWORKING_UTILITY_INSECURE_SOCKET_HANDLER_H_
#define MODEL_NETWORKING_UTILITY_INSECURE_SOCKET_HANDLER_H_

#include "socket-handler.h"
#include "../messages/message.h"

namespace model {
  class InsecureSocketHandler : public SocketHandler {
    public:
      int Send(int sockfd, Message *message);
      std::string Recv(int sockfd);
  };
}  // namespace model_networking_utility

#endif