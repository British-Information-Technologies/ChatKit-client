#ifndef CPPCHATCLIENT_MODEL_CLIENTMODEL_
#define CPPCHATCLIENT_MODEL_CLIENTMODEL_

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

#include "../utility/derived-data.h"
#include "../utility/memory-manager.h"

namespace networking_server {
class ServerConnection {
 private:
  int sockfd;
  networking_utility::DerivedData *key;

  const int buffer_size = 1024;
  char *input_buffer;
  int read_bytes;
  int read_index;

 private:
  void *get_in_addr(struct sockaddr *);

 public:
  ServerConnection();
  ~ServerConnection();

  int create_connection(std::string &, std::string &);
  int send_message(networking_utility::secure_string &);
  networking_utility::secure_string read_message();
};
}  // namespace networking_server

#endif