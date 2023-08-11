#include <memory>
#include <string>
#include <algorithm>
#include <sodium.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <netdb.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/util.h>
#include "msd/channel.hpp"

#include "connection.h"

#include "utility/data-handler.h"
#include "utility/insecure-data-handler.h"
#include "utility/secure-data-handler.h"

#include "messages/message.h"
#include "messages/internal/event-error.h"

using namespace model;

// get sockaddr, IPv4 or IPv6:
void *Connection::GetInAddr(struct sockaddr *sa) {
  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void Connection::SetState(DataHandler *next_handler) {
  data_handler.reset(next_handler);
}

Connection::Connection(
  std::shared_ptr<event_base> base,
  msd::channel<std::shared_ptr<Data>> &network_manager_chann,
  const std::string &ip_address, 
  const std::string &port
): out_chann(network_manager_chann)
{
  this->ip_address = ip_address;
  this->port = port;

  this->pk = nullptr;
  this->sk = nullptr;
  
  this->bev.reset(bufferevent_socket_new(base.get(), -1, BEV_OPT_CLOSE_ON_FREE),
    [](bufferevent *b){
      bufferevent_free(b);
    }
  );
  
  this->data_handler = nullptr;
}

Connection::~Connection() {
}

int Connection::CreateConnection() {
  if (!bev.get()) {
    // panic! failed to create connection - bev is null
    return -1;
  }
  
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
  int sockfd;
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
   
  bufferevent_setfd(bev.get(), sockfd);

  bufferevent_setcb(bev.get(), ReadMessageCbHandler, WriteMessageCbHandler, EventCbHandler, this);
  
  if (bufferevent_enable(bev.get(), EV_READ) != 0) {
    // panic! failed to enable event socket read
    return -1;
  }

  if (bufferevent_enable(bev.get(), EV_WRITE) != 0) {
    // panic! failed to enable event socket write
    return -1;
  }

  SetState(new InsecureDataHandler());

  return sockfd;
}

int Connection::SendPublicKey() {
  // ensures operations are thread safe
  if (sodium_init() < 0) {
    // sodium initialisation failed
    return -1;
  }
  
  // generate keypair
  pk = std::unique_ptr<unsigned char[]>(new unsigned char[crypto_box_PUBLICKEYBYTES]);  
  sk = std::unique_ptr<unsigned char[]>(new unsigned char[crypto_box_SECRETKEYBYTES]);  
  if(crypto_box_keypair(pk.get(), sk.get()) != 0) {
    // keypair generation failed
    return -1;
  }
  
  // convert pk into message format
  std::string str_pk(reinterpret_cast<char const*>(pk.get()), crypto_box_PUBLICKEYBYTES);
  std::unique_ptr<Message> msg_pk;
  if (DeserializeStreamOut(msg_pk.get(), str_pk) != 0) {
    // failed to create PK message
    return -1;
  }

  // send our PK as plaintext
  if (SendMessage(msg_pk.get()) < 0) {
    // failed to send PK
    return -1;
  }

  return 0;
}

int Connection::EstablishSecureConnection(const unsigned char *recv_pk) {
  // ensures operations are thread safe
  if (sodium_init() < 0) {
    // sodium initialisation failed
    return -1;
  }

  // ensure a pk and sk pair exist
  if (!pk.get() || !sk.get()) {
    // no pk and sk pair exist
    return -1;
  }

  // create shared secret with recipient PK and our SK
  unsigned char ss[crypto_box_BEFORENMBYTES];
  if(crypto_box_beforenm(ss, recv_pk, sk.get()) != 0) {
    // shared secret creation failed
    return -1;
  }

  SetState(new SecureDataHandler(ss));

  return 0;
}

void Connection::ReadMessageCbHandler(struct bufferevent *bev, void *ptr) {
  Connection *conn = static_cast<Connection *>(ptr);
  conn->ReadMessageCb();
}

void Connection::WriteMessageCbHandler(struct bufferevent *bev, void *ptr) {
  Connection *conn = static_cast<Connection *>(ptr);
  conn->WriteMessageCb();
}

void Connection::WriteMessageCb() {
  printf("<data successfully written to socket>");
}

void Connection::EventCbHandler(struct bufferevent *bev, short events, void *ptr) {
  Connection *conn = static_cast<Connection *>(ptr);
  conn->EventCb(events);
}

void Connection::EventCb(short events) {
  if (events && (BEV_EVENT_ERROR || BEV_EVENT_READING || BEV_EVENT_WRITING)) {
    printf("Buffer Event Error! Terminating Connection!\n");

    /* send data to network manager - todo add message factory
    json data = {
      { "sockfd", bufferevent_getfd(bev.get()) },
      { "internal", internal::EventError("Buffer Event Error! Terminating Connection!").Serialize() },
    };

    bufferevent_free(bev.get());
    
    data >> out_chann;*/
  }
}