#ifndef MODEL_NETWORKING_CONNECTION_H_
#define MODEL_NETWORKING_CONNECTION_H_

#include <string>

#include "utility/socket-handler.h"

namespace networking {

class Connection {
 protected:
  std::string ip_address;

  std::string port;

  networking_utility::SocketHandler *socket_handler;

 private:
  virtual void set_state(networking_utility::SocketHandler *) = 0;

 public:
  Connection(const std::string &ip_address, const std::string &port);

  ~Connection();

  virtual int create_connection() = 0;

  virtual int send_message(std::string &) = 0;

  virtual std::unique_ptr<chat_client_model_message_functionality::Message>
  read_message() = 0;
};

}  // namespace networking

#endif