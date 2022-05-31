#ifndef TEST_MODEL_TEMPORARY_CLIENT_H_
#define TEST_MODEL_TEMPORARY_CLIENT_H_

#include <arpa/inet.h>
#include <sys/socket.h>

#include <string>

class TemporaryClient {
 private:
  std::string ip;
  std::string port;
  int sockfd;

  pthread_t listener_id;
  int new_fd;

  socklen_t sin_size;
  struct sockaddr_storage their_addr;  // connector's address information
  char s[INET6_ADDRSTRLEN];

  private:
  static void *ListenForConnectionWrapper(void *context);

  void *ListenForConnection(void);

  // get sockaddr, IPv4 or IPv6:
  void *GetInAddr(struct sockaddr *sa);

 public:
  TemporaryClient(std::string ip, std::string port);

  ~TemporaryClient();

  int SetUp();

  void Listen();

  void TearDown();
};

#endif