#ifndef MODEL_NETWORKING_UTILITY_SECURE_SOCKET_HANDLER_H_
#define MODEL_NETWORKING_UTILITY_SECURE_SOCKET_HANDLER_H_

#include <memory.h>
#include <sodium.h>

#include "socket-handler.h"

namespace model_networking_utility {
class SecureSocketHandler : public SocketHandler {
 private:
  //unsigned char *ss;
  std::unique_ptr<unsigned char> ss;

 public:
  SecureSocketHandler(unsigned char *ss);

  int Send(int sockfd, model_message_functionality::Message *message);
  std::string Recv(int sockfd);
};
}  // namespace model_networking_utility

#endif