#ifndef TEST_MODEL_TEMPORARY_CLIENT_H_
#define TEST_MODEL_TEMPORARY_CLIENT_H_

#include <sys/socket.h>

#include <string>

class TemporaryClient {
 private:
  std::string ip;
  std::string port;
  int sockfd;

  void *get_in_addr(struct sockaddr *sa);

 public:
  TemporaryClient(std::string ip, std::string port);

  ~TemporaryClient();

  int setup();

  void teardown();
};

#endif