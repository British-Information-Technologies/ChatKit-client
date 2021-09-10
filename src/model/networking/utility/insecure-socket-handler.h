#ifndef CPPCHATCLIENT_INSECURE_SOCKET_HANDLER_H_
#define CPPCHATCLIENT_INSECURE_SOCKET_HANDLER_H_

#include "socket-handler.h"

namespace networking_utility {
class InsecureSocketHandler : public SocketHandler {
 public:
  InsecureSocketHandler(int);

  int send(chat_client_model_message_functionality::Message *);
  std::string recv(std::string &payload);
};
}  // namespace networking_utility

#endif