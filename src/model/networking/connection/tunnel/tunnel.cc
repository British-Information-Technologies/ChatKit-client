#include <memory>
#include <string>
#include <algorithm>
#include <sodium.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <netdb.h>
#include <event2/listener.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/util.h>
#include <iostream>
#include "msd/channel.hpp"

#include "tunnel.h"

#include "model/networking/connection/tunnel/data-handler/data-handler.h"
#include "model/networking/connection/tunnel/data-handler/insecure-data-handler.h"
#include "model/networking/connection/tunnel/data-handler/secure-data-handler.h"
#include "model/networking/utility/encode.h"

#include "model/networking/messages/message.h"
#include "model/networking/messages/internal/event-error.h"

#include "model/networking/connection/callback/io-callbacks.h"

using namespace model;

// get sockaddr, IPv4 or IPv6:
void *Tunnel::GetInAddr(struct sockaddr *sa) {
  return &(((struct sockaddr_in *)sa)->sin_addr);
}

std::tuple<unsigned char*, unsigned char*> Tunnel::GenerateKeyPair() {
  // ensures operations are thread safe
  if (sodium_init() < 0) {
    // sodium initialisation failed
    return std::make_tuple(nullptr, nullptr);
  }

  // generate keypair
  unsigned char *public_key = (unsigned char*) malloc(sizeof(unsigned char[crypto_kx_PUBLICKEYBYTES]));
  unsigned char *secret_key = (unsigned char*) malloc(sizeof(unsigned char[crypto_kx_SECRETKEYBYTES]));

  if(crypto_kx_keypair(public_key, secret_key) != 0) {
    // keypair generation failed
    free(public_key);
    free(secret_key);

    return std::make_tuple(nullptr, nullptr);
  }
  
  return std::make_tuple(public_key, secret_key);
}

void Tunnel::SetState(DataHandler *next_handler) {
  data_handler.reset(next_handler);
}

void Tunnel::SetBev(bufferevent *bev) {
  this->bev.reset(
    bev,
    [](bufferevent *b){
      bufferevent_free(b);
    }
  );  
}

const char* Tunnel::GetIpAddress()
{
  return ip_address.c_str();
}

int Tunnel::GetPort()
{
  return std::stoi(port);
}

Tunnel::Tunnel(
  const TunnelType type,
  std::shared_ptr<Connection> connection,
  std::shared_ptr<event_base> base,
  const std::string &ip_address, 
  const std::string &port,
  unsigned char *public_key,
  unsigned char *secret_key
):type(type),
  connection(connection),
  ip_address(ip_address),
  port(port),
  data_handler(new InsecureDataHandler),
  public_key(public_key),
  secret_key(secret_key)
{
  this->bev.reset(bufferevent_socket_new(base.get(), -1, BEV_OPT_CLOSE_ON_FREE),
    [](bufferevent *b){
      bufferevent_free(b);
    }
  );  
}

bool Tunnel::IsSecure() {
  return data_handler->GetType() == DataHandlerType::Secure;
}

const TunnelType Tunnel::GetType() {
  return type;
}

const std::string Tunnel::GetPublicKey() {
  return Bin2Base64(public_key.get(), crypto_kx_PUBLICKEYBYTES);
}

int Tunnel::Initiate()
{
  if (!bev.get()) {
    // panic! failed to create connection - bev is null
    return -1;
  }
  
  struct addrinfo hints, *servinfo, *p;
  int rv;
  char s[INET_ADDRSTRLEN]; // add a 6 to INET to make it work with ivp 6 - remove 6 for ivp 4

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;  // add a 6 to make it work with ivp 6 - remove 6 for ivp 4
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  if ((rv = getaddrinfo(ip_address.c_str(), port.c_str(), &hints, &servinfo)) != 0) {
    fprintf(stderr, "[Tunnel]: getaddrinfo = %s\n", gai_strerror(rv));
    return -1;
  }

  // loop through all the results and connect to the first we can
  int sockfd;
  for (p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      perror("[Tunnel]: socket creation failed\n");
      continue;
    }

    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("[Tunnel]: open socket failed\n");
      continue;
    }

    break;
  }

  if (p == NULL) {
    fprintf(stderr, "[Tunnel]: failed to connect\n");
    return -1;
  }

  inet_ntop(p->ai_family, GetInAddr((struct sockaddr *)p->ai_addr), s, sizeof s);

  printf("[Tunnel]: connecting to %s\n", s);

  freeaddrinfo(servinfo);  // all done with this structure
   
  bufferevent_setfd(bev.get(), sockfd);
 
  switch (GetType()) {
    case TunnelType::Client:
      IOCallbacks::SetClientConnectionCallbacks(bev.get(), connection.get());
      break;

    case TunnelType::Server:
      IOCallbacks::SetServerConnectionCallbacks(bev.get(), connection.get());
  }
  
  if (bufferevent_enable(bev.get(), EV_READ|EV_WRITE) != 0) {
    // panic! failed to enable event socket read and write
    return -1;
  }

  SetState(new InsecureDataHandler());

  return 0;
}

int Tunnel::EstablishSecureTunnel(Party party, const unsigned char *recv_pk) {
  // ensures operations are thread safe
  if (sodium_init() < 0) {
    // sodium initialisation failed
    return -1;
  }

  // create shared secret with recipient PK and our SK
  unsigned char *session_key_rx = (unsigned char*) malloc(sizeof(unsigned char[crypto_kx_SESSIONKEYBYTES]));
  unsigned char *session_key_tx = (unsigned char*) malloc(sizeof(unsigned char[crypto_kx_SESSIONKEYBYTES]));
  
  int res = (party == Party::One) ?
    crypto_kx_server_session_keys(
      session_key_rx,
      session_key_tx,
      public_key.get(),
      secret_key.get(),
      recv_pk
    ) :
    crypto_kx_client_session_keys(
      session_key_rx,
      session_key_tx,
      public_key.get(),
      secret_key.get(),
      recv_pk
    );

  if(res) {
    // shared secret creation failed
    free(session_key_rx);
    free(session_key_tx);
    
    return -1;
  }

  SetState(new SecureDataHandler(session_key_rx, session_key_tx));

  return 0;
}

std::string Tunnel::ReadMessage(std::string &data)
{
  return data_handler->FormatRead(data);
}