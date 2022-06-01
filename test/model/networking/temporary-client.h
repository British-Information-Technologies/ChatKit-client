#ifndef TEST_MODEL_TEMPORARY_CLIENT_H_
#define TEST_MODEL_TEMPORARY_CLIENT_H_

#include <sys/socket.h>
#include <string>

class TemporaryClient {
 private:
  std::string ip;
  std::string port;
  int sockfd;

  // get sockaddr, IPv4 or IPv6:
  void *GetInAddr(struct sockaddr *sa);

 public:
  TemporaryClient(std::string ip, std::string port);

  ~TemporaryClient();

  int SetUp();

  void TearDown();
};

#endif