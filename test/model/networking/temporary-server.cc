#include "temporary-server.h"

#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BACKLOG 1  // how many pending connections queue will hold

void *TemporaryServer::ListenForConnectionWrapper(void *context) {
  return ((TemporaryServer *)context)->ListenForConnection();
}

void *TemporaryServer::ListenForConnection(void) {
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
void *TemporaryServer::get_in_addr(struct sockaddr *sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in *)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

TemporaryServer::TemporaryServer(std::string ip, std::string port) {
  this->ip = ip;
  this->port = port;
}

TemporaryServer::~TemporaryServer() { this->teardown(); }

int TemporaryServer::setup() {
  struct addrinfo hints, *servinfo, *p;
  int yes = 1;
  int rv;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;  // use my IP

  if ((rv = getaddrinfo(ip.c_str(), port.c_str(), &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    exit(1);
  }

  if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
                       servinfo->ai_protocol)) == -1) {
    perror("server: socket");
    exit(1);
  }

  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
    perror("setsockopt");
    exit(1);
  }

  if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
    close(sockfd);
    perror("server: bind");
    exit(1);
  }

  freeaddrinfo(servinfo);  // all done with this structure

  if (p == NULL) {
    fprintf(stderr, "server: failed to bind\n");
    exit(1);
  }

  if (listen(sockfd, BACKLOG) == -1) {
    perror("listen");
    exit(1);
  }

  /* Listen on a thread so test can still occur */
  pthread_create(&listener_id, NULL,
                 &TemporaryServer::ListenForConnectionWrapper, this);

  return 1;
}

void TemporaryServer::teardown() {
  pthread_join(listener_id, NULL);

  close(sockfd);
  close(new_fd);
}