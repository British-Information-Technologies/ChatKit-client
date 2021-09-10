#ifndef TEST_MODEL_TEMPORARY_SERVER_H_
#define TEST_MODEL_TEMPORARY_SERVER_H_

#include <arpa/inet.h>
#include <sys/socket.h>

#include <string>

class TemporaryServer {
 public:
  pthread_t listener_id;
  int new_fd;

 private:
  std::string ip;
  std::string port;
  int sockfd;  // listen on sock_fd, new connection on new_fd
  socklen_t sin_size;
  struct sockaddr_storage their_addr;  // connector's address information
  char s[INET6_ADDRSTRLEN];

  static void *ListenForConnectionWrapper(void *context);

  void *ListenForConnection(void);

  // get sockaddr, IPv4 or IPv6:
  void *get_in_addr(struct sockaddr *sa);

 public:
  TemporaryServer(std::string ip, std::string port);

  ~TemporaryServer();

  int setup();

  void teardown();
};

#endif