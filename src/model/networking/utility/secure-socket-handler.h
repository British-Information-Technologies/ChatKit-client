#ifndef MODEL_NETWORKING_UTILITY_SECURE_SOCKET_HANDLER_H_
#define MODEL_NETWORKING_UTILITY_SECURE_SOCKET_HANDLER_H_

#include "derived-data.h"
#include "socket-handler.h"

namespace model_networking_utility {
class SecureSocketHandler : public SocketHandler {
 private:
  DerivedData *key;

 public:
  SecureSocketHandler(int, DerivedData *);
  ~SecureSocketHandler();

  int Send(model_message_functionality::Message *);
  std::string Recv(std::string &payload);
};
}  // namespace model_networking_utility

#endif