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

  int sockfd;
  
 private:
  void *GetInAddr(struct sockaddr *);

  virtual int GetRecipientPublicKey(unsigned char* recv_pk) = 0;
  
  virtual void SetState(model_networking_utility::SocketHandler *) = 0;

 protected:
  int CreateConnection();

 public:
  Connection(const std::string &ip_address, const std::string &port);

  ~Connection();

  virtual int SendPublicKey() = 0;

  virtual int EstablishSecureConnection() = 0;

  virtual int SendMessage(std::string &) = 0;

  virtual std::unique_ptr<model_message_functionality::Message> ReadMessage() = 0;
};

}  // namespace model_networking

#endif