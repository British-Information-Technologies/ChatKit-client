#include "server-connection.h"

#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <netdb.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#include <algorithm>
#include <nlohmann/json.hpp>

#include "../../message-functionality/client-stream-in-factory.h"
#include "../../message-functionality/client-stream-out-factory.h"
#include "../../message-functionality/network-stream-in-factory.h"
#include "../../message-functionality/network-stream-out-factory.h"
#include "../utility/aes-gcm.h"
#include "../utility/elliptic-curve-diffiehellman.h"
#include "../utility/insecure-socket-handler.h"
#include "../utility/secure-socket-handler.h"
#include "../utility/sha-3-256.h"

using namespace model_networking_server;
using namespace model_message_functionality;
using namespace model_networking_utility;
using json = nlohmann::json;

// get sockaddr, IPv4 or IPv6:
void *ServerConnection::GetInAddr(struct sockaddr *sa) {
  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void ServerConnection::SetState(SocketHandler *next_handler) {
  delete socket_handler;
  socket_handler = next_handler;
}

void ServerConnection::SetFactoryState(
    std::shared_ptr<ServerStreamOutFactory> stream_out_factory,
    std::shared_ptr<ServerStreamInFactory> stream_in_factory) {
  this->stream_out_factory = stream_out_factory;
  this->stream_in_factory = stream_in_factory;
}

ServerConnection::ServerConnection(const std::string &ip_address,
                                   const std::string &port)
    : Connection(ip_address, port), key_pair(GenerateKeyPair()) {
  this->sockfd = -1;
  this->stream_out_factory = std::make_shared<NetworkStreamOutFactory>();
  this->stream_in_factory = std::make_shared<NetworkStreamInFactory>();
}

int ServerConnection::CreateConnection() {
  struct addrinfo hints, *servinfo, *p;
  int rv;
  char s[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET6;
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
      perror("client: socket");
      continue;
    }

    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("client: connect");
      continue;
    }

    break;
  }

  if (p == NULL) {
    fprintf(stderr, "client: failed to connect\n");
    return -1;
  }

  inet_ntop(p->ai_family, GetInAddr((struct sockaddr *)p->ai_addr), s,
            sizeof s);
  printf("client: connecting to %s\n", s);

  freeaddrinfo(servinfo);  // all done with this structure

  SetState(new InsecureSocketHandler(sockfd));

  return sockfd;
}

int ServerConnection::SendPublicKey() {
  EVP_PKEY_free_ptr public_key = ExtractPublicKey(key_pair.get());

  /*public keys need to be shared with other party at this point*/
  std::string serial_public_key = SerializePublicKey(public_key.get());

  return SendMessage(serial_public_key);
}

int ServerConnection::EstablishSecureConnection(Message *message) {
  if (sockfd < 0 || key_pair == nullptr) {
    return -1;
  }

  EVP_PKEY_free_ptr peer_public_key =
      DeserializePublicKey(message->ToString().c_str());

  /*Create the shared secret with other users public key and your
    own private key (this has wrong public key as a place holder*/
  DerivedData *key = DeriveSharedSecret(peer_public_key.get(), key_pair.get());

  /*Hash the secret to create the key*/
  HashData(key);

  SetState(new SecureSocketHandler(sockfd, key));
  SetFactoryState(std::make_shared<ClientStreamOutFactory>(),
                  std::make_shared<ClientStreamInFactory>());

  return 1;
}

int ServerConnection::SendMessage(std::string &plaintext) {
  std::unique_ptr<Message> message = stream_out_factory->GetMessage(plaintext);

  int sent_bytes = socket_handler->Send(message.get());

  return sent_bytes;
}

std::unique_ptr<Message> ServerConnection::TranslateMessage(std::string &line) {
  std::string json_string = socket_handler->Recv(line);
  std::cout << json_string << std::endl;

  std::unique_ptr<Message> message = stream_in_factory->GetMessage(json_string);

  return message;
}