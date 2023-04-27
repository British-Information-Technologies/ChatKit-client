#ifndef MODEL_NETWORKING_CONNECTION_H_
#define MODEL_NETWORKING_CONNECTION_H_

#include <string>
#include <sodium.h>

#include "utility/socket-handler.h"

namespace model_networking {

class Connection {
 protected:
  std::string ip_address;

  std::string port;

  model_networking_utility::SocketHandler *socket_handler;

 private:
  int sockfd;
  unsigned char pk[crypto_box_PUBLICKEYBYTES];
  unsigned char sk[crypto_box_SECRETKEYBYTES];
  unsigned char nonce[crypto_box_NONCEBYTES];
  unsigned char ss[crypto_box_BEFORENMBYTES];

  unsigned char recv_pk[crypto_box_PUBLICKEYBYTES];

 private:
  void *GetInAddr(struct sockaddr *);

  int GetRecipientPublicKey();
  
  virtual void SetState(model_networking_utility::SocketHandler *) = 0;

 public:
  Connection(const std::string &ip_address, const std::string &port);

  ~Connection();

  int CreateConnection();

  virtual int SendPublicKey() = 0;

  int EstablishSecureConnection();

  virtual int SendMessage(std::string &) = 0;

  virtual std::unique_ptr<model_message_functionality::Message>
  TranslateMessage(std::string &line) = 0;
};

}  // namespace model_networking

#endif