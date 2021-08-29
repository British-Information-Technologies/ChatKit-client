#ifndef CPPCHATCLIENT_MODEL_CLIENTMODEL_H_
#define CPPCHATCLIENT_MODEL_CLIENTMODEL_H_

#include "../../message-functionality/server-stream-in-factory.h"
#include "../../message-functionality/server-stream-out-factory.h"
#include "../connection.h"

namespace networking_server {
class ServerConnection : public networking::Connection {
 private:
  std::shared_ptr<
      chat_client_model_message_functionality::ServerStreamOutFactory>
      stream_out_factory;

  std::shared_ptr<
      chat_client_model_message_functionality::ServerStreamInFactory>
      stream_in_factory;

 private:
  void *get_in_addr(struct sockaddr *);

  void set_state(networking_utility::SocketHandler *);

  void set_factory_state(
      std::shared_ptr<
          chat_client_model_message_functionality::ServerStreamOutFactory>
          stream_out_factory,
      std::shared_ptr<
          chat_client_model_message_functionality::ServerStreamInFactory>
          stream_in_factory);

 public:
  ServerConnection(const std::string &ip_address, const std::string &port);

  int create_connection();

  int send_message(std::string &);

  std::unique_ptr<chat_client_model_message_functionality::Message>
  read_message();
};
}  // namespace networking_server

#endif