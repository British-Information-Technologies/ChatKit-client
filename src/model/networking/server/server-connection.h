#ifndef CPPCHATCLIENT_MODEL_CLIENTMODEL_H_
#define CPPCHATCLIENT_MODEL_CLIENTMODEL_H_

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>

#include "../utility/buffer-reader.h"
#include "../utility/derived-data.h"
#include "../utility/memory-manager.h"
#include "../utility/socket-handler.h"

namespace networking_server {
class ServerConnection {
 private:
  networking_utility::SocketHandler *socket_handler;

 private:
  void *get_in_addr(struct sockaddr *);
  void set_state(networking_utility::SocketHandler *);

 public:
  ServerConnection();
  ~ServerConnection();

  int create_connection(std::string &, std::string &);
  int send_message(networking_utility::secure_string &);
  networking_utility::secure_string read_message();
};
}  // namespace networking_server

#endif