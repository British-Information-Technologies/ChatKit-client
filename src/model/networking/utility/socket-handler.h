#ifndef MODEL_NETWORKING_UTILITY_SOCKET_HANDLER_H_
#define MODEL_NETWORKING_UTILITY_SOCKET_HANDLER_H_

#include <string>

#include "../../message-functionality/message.h"

namespace model_networking_utility {
class SocketHandler {
  public:
    virtual int Send(int sockfd, model_message_functionality::Message *message) = 0;
    virtual std::string Recv(int sockfd) = 0;
};
}  // namespace model_networking_utility

#endif