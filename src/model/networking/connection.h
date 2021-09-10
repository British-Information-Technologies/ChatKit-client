#ifndef MODEL_NETWORKING_CONNECTION_H_
#define MODEL_NETWORKING_CONNECTION_H_

#include <string>

#include "utility/socket-handler.h"

namespace model_networking {

class Connection {
 protected:
  std::string ip_address;

  std::string port;

  model_networking_utility::SocketHandler *socket_handler;

 private:
  virtual void set_state(model_networking_utility::SocketHandler *) = 0;

 public:
  Connection(const std::string &ip_address, const std::string &port);

  ~Connection();

  virtual int create_connection() = 0;

  virtual int establish_secure_connection(
      model_message_functionality::Message *message) = 0;

  virtual int send_message(std::string &) = 0;

  virtual std::unique_ptr<model_message_functionality::Message>
  translate_message(std::string &line) = 0;
};

}  // namespace model_networking

#endif