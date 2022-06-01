#ifndef MODEL_NETWORKING_UTILITY_INSECURE_SOCKET_HANDLER_H_
#define MODEL_NETWORKING_UTILITY_INSECURE_SOCKET_HANDLER_H_

#include "socket-handler.h"

namespace model_networking_utility {
class InsecureSocketHandler : public SocketHandler {
 public:
  InsecureSocketHandler(int);

  int Send(model_message_functionality::Message *);
  std::string Recv(std::string &payload);
};
}  // namespace model_networking_utility

#endif