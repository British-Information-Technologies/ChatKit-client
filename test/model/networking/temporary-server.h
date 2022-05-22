#ifndef TEST_MODEL_TEMPORARY_SERVER_H_
#define TEST_MODEL_TEMPORARY_SERVER_H_

#include <arpa/inet.h>
#include <sys/socket.h>

#include <string>

#include "model/networking/utility/derived-data.h"
#include "model/networking/utility/socket-handler.h"

class TemporaryServer {
 public:
  pthread_t listener_id;
  int new_fd;

 private:
  model_networking_utility::DerivedData *key = nullptr;
  model_networking_utility::SocketHandler *socket_handler = nullptr;

  std::string ip;
  std::string port;
  int sockfd;  // listen on sock_fd, new connection on new_fd
  socklen_t sin_size;
  struct sockaddr_storage their_addr;  // connector's address information
  char s[INET6_ADDRSTRLEN];

 private:
  static void *ListenForConnectionWrapper(void *context);

  void *ListenForConnection(void);

  // get sockaddr, IPv4 or IPv6:
  void *GetInAddr(struct sockaddr *sa);

 public:
  TemporaryServer(std::string ip, std::string port);

  ~TemporaryServer();

  int SetUp();

  void TearDown();

  void SetState(model_networking_utility::SocketHandler *next_handler);
};

#endif