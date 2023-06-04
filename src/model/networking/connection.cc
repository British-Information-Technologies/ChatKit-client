#include <memory>
#include <string>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <netdb.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/util.h>
#include <nlohmann/json.hpp>
#include "msd/channel.hpp"

#include "connection.h"

#include "utility/data-handler.h"
#include "utility/insecure-data-handler.h"

#include "messages/message.h"
#include "messages/internal/event-error.h"

#include "utility/buffer-reader.h"
#include "utility/buffer-writer.h"

using namespace model;

using json = nlohmann::json;

// get sockaddr, IPv4 or IPv6:
void *Connection::GetInAddr(struct sockaddr *sa) {
  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void Connection::SetState(DataHandler *next_handler) {
  data_handler.reset(next_handler);
}

Connection::Connection(std::shared_ptr<event_base> base, msd::channel<json> &network_manager_chann, const std::string &ip_address, const std::string &port):
out_chann(network_manager_chann) {
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

int Connection::SendMessage(Message *message) {
  std::string msg_str = message->Serialize();
  std::string encoded_packet = data_handler->FormatSend(msg_str);
  
  if (!encoded_packet.length()) {
    // encoded packet is empty, failed to format message
    return -1;
  }

  // send encoded packet
  return WriteBufferLine(bev, encoded_packet);
}

void Connection::ReadMessageCbHandler(struct bufferevent *bev, void *ptr) {
  Connection *conn = static_cast<Connection *>(ptr);
  conn->ReadMessageCb();
}

void Connection::ReadMessageCb() {
  // read encoded packet
  std::string encoded_packet = ReadBufferLine(bev);

  // decode or decode and decrypt data
  std::string plaintext = data_handler->FormatRead(encoded_packet);

  if (!plaintext.length()) {
    // plaintext is empty, failed to format encoded packet
    return;
  }

  // send data to network manager
  json data = {
    { "sockfd", bufferevent_getfd(bev.get()) },
    { "plaintext", plaintext },
  };

  data >> out_chann; 
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

    // send data to network manager - todo add message factory
    json data = {
      { "sockfd", bufferevent_getfd(bev.get()) },
      { "internal", internal::EventError("Buffer Event Error! Terminating Connection!").Serialize() },
    };

    bufferevent_free(bev.get());
    
    data >> out_chann;
  }
}