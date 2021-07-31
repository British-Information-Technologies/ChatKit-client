#include "server-connection.h"

#include <bits/stdc++.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#include <nlohmann/json.hpp>

#include "../utility/aes-gcm.h"
#include "../utility/elliptic-curve-diffiehellman.h"
#include "../utility/sha-3-256.h"

using namespace networking_server;
using namespace networking_utility;
using json = nlohmann::json;

// get sockaddr, IPv4 or IPv6:
void *ServerConnection::get_in_addr(struct sockaddr *sa) {
  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int ServerConnection::create_connection(std::string &ip_address,
                                        std::string &port) {
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

  /* Create shared secret */
  EVP_PKEY_free_ptr key_pair = GenerateKeyPair();
  EVP_PKEY_free_ptr public_key = ExtractPublicKey(key_pair.get());

  /*public keys need to be shared with other party at this point*/
  std::string serial_public_key = SerializePublicKey(public_key.get());

  int sent_bytes = send(sockfd, serial_public_key.c_str(),
                        serial_public_key.length() + 1, 0);

  int buffer_size = 1024;
  char buffer[buffer_size];
  int read_bytes = read_message(buffer, buffer_size);

  EVP_PKEY_free_ptr peer_public_key = DeserializePublicKey(buffer);

  /*Create the shared secret with other users public key and your
    own private key (this has wrong public key as a place holder*/
  key = DeriveSharedSecret(peer_public_key.get(), key_pair.get());

  /*Hash the secret to create the key*/
  HashData(key);

  return 1;
}

int ServerConnection::send_message(secure_string &plaintext) {
  if (plaintext.length() <= 0) return 0;

  /*Encrypt the message with the key, aad, and iv*/
  secure_string aad = "address:port";  // faked value
  const int iv_size = 12;
  byte iv[iv_size + 1];

  int rc = RAND_bytes(iv, iv_size);
  unsigned long err = ERR_get_error();
  if (rc != 1) {
    /* show error */
    return 0;
  }
  iv[iv_size] = '\0';

  const int tag_size = 16;
  byte tag[tag_size + 1];
  tag[tag_size] = '\0';

  secure_string ciphertext;
  int ciphertext_len =
      aes_gcm_encrypt(plaintext, aad, key, iv, iv_size, ciphertext, tag);

  /*Format the message into a json string (serialize)*/
  json json_object = {
      {"message", ciphertext}, {"aad", aad}, {"iv", iv}, {"tag", tag}};
  std::string message = json_object.dump();

  /*Send message*/
  int sent_bytes = send(sockfd, message.c_str(), message.length() + 1, 0);

  return sent_bytes;
}

int ServerConnection::read_message(char *buffer, size_t buffer_size) {
  int numbytes = recv(sockfd, buffer, buffer_size - 1, 0);

  *(buffer + buffer_size) = '\0';

  return numbytes;
}