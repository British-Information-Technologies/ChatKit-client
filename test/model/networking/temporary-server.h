#ifndef TEMPORARY_SERVER_H_
#define TEMPORARY_SERVER_H_

#include <arpa/inet.h>
#include <sys/socket.h>

#include <string>

class TemporaryServer {
 private:
  std::string ip;
  std::string port;
  pthread_t listener_id;
  int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
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