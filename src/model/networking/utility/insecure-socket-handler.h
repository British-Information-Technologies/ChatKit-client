#ifndef CPPCHATCLIENT_INSECURE_SOCKET_HANDLER_H_
#define CPPCHATCLIENT_INSECURE_SOCKET_HANDLER_H_

#include "socket-handler.h"

namespace networking_utility {
class InsecureSocketHandler : public SocketHandler {
 public:
  InsecureSocketHandler(int);

  int send(secure_string &);
  secure_string recv();
};
}  // namespace networking_utility

#endif