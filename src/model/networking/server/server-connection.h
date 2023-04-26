#ifndef MODEL_NETWORKING_SERVER_SERVER_CONNECTION_H_
#define MODEL_NETWORKING_SERVER_SERVER_CONNECTION_H_

#include "../../message-functionality/server-stream-in-factory.h"
#include "../../message-functionality/server-stream-out-factory.h"
#include "../connection.h"
#include "../utility/crypto-types.h"

namespace model_networking_server {
class ServerConnection : public model_networking::Connection {
 private:
  int sockfd;

  EVP_PKEY_free_ptr key_pair;

  std::shared_ptr<model_message_functionality::ServerStreamOutFactory>
      stream_out_factory;

  std::shared_ptr<model_message_functionality::ServerStreamInFactory>
      stream_in_factory;

 private:
  void SetState(model_networking_utility::SocketHandler *);

  void SetFactoryState(
      std::shared_ptr<model_message_functionality::ServerStreamOutFactory>
          stream_out_factory,
      std::shared_ptr<model_message_functionality::ServerStreamInFactory>
          stream_in_factory);

 public:
  ServerConnection(const std::string &ip_address, const std::string &port);

  int SendPublicKey();

  int EstablishSecureConnection(model_message_functionality::Message *message);

  int SendMessage(std::string &);

  std::unique_ptr<model_message_functionality::Message> TranslateMessage(
      std::string &line);
};
}  // namespace model_networking_server

#endif