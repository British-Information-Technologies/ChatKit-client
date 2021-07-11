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

#include <nlohmann/json.hpp>
#include <string>

namespace networking_server {
class ServerConnection {
 private:
  int sockfd;

 private:
  void *get_in_addr(struct sockaddr *);

 public:
  int create_connection(std::string &, std::string &);
  int send_message(nlohmann::json &);
  int read_message(char *, size_t);
};
}  // namespace networking_server

#endif