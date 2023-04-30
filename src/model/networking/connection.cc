#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <netdb.h>

#include "connection.h"
#include "utility/insecure-socket-handler.h"

using namespace model_networking;
using namespace model_networking_utility;

// get sockaddr, IPv4 or IPv6:
void *Connection::GetInAddr(struct sockaddr *sa) {
  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int Connection::CreateConnection() {
  struct addrinfo hints, *servinfo, *p;
  int rv;
  char s[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET6;  // add a 6 to make it work with ivp 6 - remove 6 for ivp 4
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  if ((rv = getaddrinfo(ip_address.c_str(), port.c_str(), &hints, &servinfo)) !=
      0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return -1;
  }

  // loop through all the results and connect to the first we can
  for (p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      perror("connection: socket creation failed");
      continue;
    }

    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("connection: open socket failed");
      continue;
    }

    break;
  }

  if (p == NULL) {
    fprintf(stderr, "connection: failed to connect\n");
    return -1;
  }

  inet_ntop(p->ai_family, GetInAddr((struct sockaddr *)p->ai_addr), s,
            sizeof s);

  printf("connection: connecting to %s\n", s);

  freeaddrinfo(servinfo);  // all done with this structure

  SetState(new InsecureSocketHandler());

  return 0;
}

Connection::Connection(const std::string &ip_address, const std::string &port) {
  this->ip_address = ip_address;
  this->port = port;
  this->socket_handler = nullptr;
  this->sockfd = -1;
}

Connection::~Connection() { delete socket_handler; }