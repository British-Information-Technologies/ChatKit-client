#include "server-connection.h"

#include <bits/stdc++.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#include <algorithm>
#include <nlohmann/json.hpp>

#include "../utility/aes-gcm.h"
#include "../utility/elliptic-curve-diffiehellman.h"
#include "../utility/insecure-socket-handler.h"
#include "../utility/secure-socket-handler.h"
#include "../utility/sha-3-256.h"

using namespace networking_server;
using namespace networking_utility;
using json = nlohmann::json;

ServerConnection::ServerConnection() { socket_handler = nullptr; }

ServerConnection::~ServerConnection() { delete socket_handler; }

// get sockaddr, IPv4 or IPv6:
void *ServerConnection::get_in_addr(struct sockaddr *sa) {
  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void ServerConnection::set_state(SocketHandler *next_handler) {
  delete socket_handler;
  socket_handler = next_handler;
}

int ServerConnection::create_connection(std::string &ip_address,
                                        std::string &port) {
  struct addrinfo hints, *servinfo, *p;
  int sockfd, rv;
  char s[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET6;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  if ((rv = getaddrinfo(ip_address.c_str(), port.c_str(), &hints, &servinfo)) !=
      0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 0;
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
    return 0;
  }

  inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s,
            sizeof s);
  printf("client: connecting to %s\n", s);

  freeaddrinfo(servinfo);  // all done with this structure

  set_state(new InsecureSocketHandler(sockfd));

  /* Create shared secret */
  EVP_PKEY_free_ptr key_pair = GenerateKeyPair();
  EVP_PKEY_free_ptr public_key = ExtractPublicKey(key_pair.get());

  /*public keys need to be shared with other party at this point*/
  std::string serial_public_key = SerializePublicKey(public_key.get());

  int sent_bytes = send(sockfd, serial_public_key.c_str(),
                        serial_public_key.length() + 1, 0);

  secure_string payload = socket_handler->recv();

  EVP_PKEY_free_ptr peer_public_key = DeserializePublicKey(payload.c_str());

  /*Create the shared secret with other users public key and your
    own private key (this has wrong public key as a place holder*/
  DerivedData *key = DeriveSharedSecret(peer_public_key.get(), key_pair.get());

  /*Hash the secret to create the key*/
  HashData(key);

  set_state(new SecureSocketHandler(sockfd, key));

  return 1;
}

int ServerConnection::send_message(secure_string &plaintext) {
  int sent_bytes = socket_handler->send(plaintext);
  return sent_bytes;
}

secure_string ServerConnection::read_message() {
  /* Possibly format message into a message object of some kind in the future */
  secure_string message = socket_handler->recv();
  return message;
}