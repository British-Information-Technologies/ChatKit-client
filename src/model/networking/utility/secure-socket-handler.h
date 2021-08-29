#ifndef CPPCHATCLIENT_SECURE_SOCKET_HANDLER_H_
#define CPPCHATCLIENT_SECURE_SOCKET_HANDLER_H_

#include "derived-data.h"
#include "socket-handler.h"

namespace networking_utility {
class SecureSocketHandler : public SocketHandler {
 private:
  DerivedData *key;

 public:
  SecureSocketHandler(int, DerivedData *);
  ~SecureSocketHandler();

  int send(chat_client_model_message_functionality::Message *);
  std::string recv();
};
}  // namespace networking_utility

#endif