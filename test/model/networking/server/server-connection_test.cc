#include "model/networking/server/server-connection.h"

#include <arpa/inet.h>
#include <errno.h>
#include <gtest/gtest.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace networking_server;

#define BACKLOG 1  // how many pending connections queue will hold

class ServerConnectionTest : public ::testing::Test {
 protected:
  std::string server_ip = "localhost";
  std::string server_port = "3490";

  pthread_t listener_id;
  int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
  socklen_t sin_size;
  struct sockaddr_storage their_addr;  // connector's address information
  char s[INET6_ADDRSTRLEN];

  void SetUp() override {
    struct addrinfo hints, *servinfo, *p;
    int yes = 1;
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;  // use my IP

    // if ((rv = getaddrinfo(NULL, server_port.c_str(), &hints, &servinfo)) !=
    // 0) {
    if ((rv = getaddrinfo(server_ip.c_str(), server_port.c_str(), &hints,
                          &servinfo)) != 0) {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      GTEST_FAIL();
      exit(1);
    }

    // loop through all the results and bind to the first we can
    // for (p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
                         servinfo->ai_protocol)) == -1) {
      perror("server: socket");
      GTEST_FAIL();
      exit(1);
      // continue;
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
      perror("setsockopt");
      GTEST_FAIL();
      exit(1);
    }

    if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
      close(sockfd);
      perror("server: bind");
      GTEST_FAIL();
      exit(1);
      // continue;
    }

    // break;
    // }

    freeaddrinfo(servinfo);  // all done with this structure

    if (p == NULL) {
      fprintf(stderr, "server: failed to bind\n");
      GTEST_FAIL();
      exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
      perror("listen");
      GTEST_FAIL();
      exit(1);
    }

    /* Listen on a thread so test can still occur */
    pthread_create(&listener_id, NULL,
                   &ServerConnectionTest::ListenForConnectionWrapper, this);
  }

  void TearDown() override {
    pthread_join(listener_id, NULL);

    close(sockfd);
    close(new_fd);
  }

  static void *ListenForConnectionWrapper(void *context) {
    return ((ServerConnectionTest *)context)->ListenForConnection();
  }

  void *ListenForConnection(void) {
    printf("server: waiting for connection...\n");

    sin_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    if (new_fd == -1) {
      perror("accept");
      exit(1);
    }

    inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr),
              s, sizeof s);
    printf("server: got connection from %s\n", s);

    return 0;
  }

  // get sockaddr, IPv4 or IPv6:
  void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
      return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
  }
};

/* TESTS */
TEST_F(ServerConnectionTest, CreateConnectionTest) {
  ServerConnection server;
  EXPECT_TRUE(server.create_connection(server_ip, server_port));
}
