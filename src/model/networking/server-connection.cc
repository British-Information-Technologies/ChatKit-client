#include "server-connection.h"

#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <netdb.h>

#include <algorithm>
#include <nlohmann/json.hpp>
#include <sodium.h>

#include "messages/message.h"
#include "messages/stream-in/server/error.h"

#include "utility/socket-handler.h"
#include "utility/insecure-socket-handler.h"
#include "utility/secure-socket-handler.h"

using namespace model;

using json = nlohmann::json;

void ServerConnection::SetState(SocketHandler *next_handler) {
  delete socket_handler;
  socket_handler = next_handler;
}

int ServerConnection::GetRecipientPublicKey(unsigned char* recv_pk) {
  // read potential PK
  auto server_pk_msg = ReadMessage();
  
  json server_pk_json = server_pk_msg->ToJson();

  // verify read message is a PK
  if (!server_pk_json.contains("PublicKey")) {
    // read message is not a PK message
    return -1;
  }
  
  // extract PK -- TODO

  // verify PK with CA -- TODO

  // put server PK into output buffer for return use
  *recv_pk = server_pk_json.at("PublicKey");

  return 0;
}

ServerConnection::ServerConnection(const std::string &ip_address,
                                   const std::string &port)
    : Connection(ip_address, port) {
}

int ServerConnection::EstablishSecureConnection() {
  if (sodium_init() < 0) {
    return -1;
  }
  
  // create a TCP connection
  if (CreateConnection() != 0) {
    // TCP connection failed
    return -1;
  }

  // generate keypair
  unsigned char pk[crypto_box_PUBLICKEYBYTES];
  unsigned char sk[crypto_box_SECRETKEYBYTES];
  if(crypto_box_keypair(pk, sk) != 0) {
    // keypair generation failed
    return -1;
  }

  // get servers public key
  unsigned char recv_pk[crypto_box_PUBLICKEYBYTES];
  if(GetRecipientPublicKey(recv_pk) != 0) {
    // failed to retrieve server public key or CA unable to verify PK
    return -1;
  }

  // send our PK as plaintext to server
  std::string str_pk(reinterpret_cast<char const*>(pk), crypto_box_PUBLICKEYBYTES);
  if(SendMessage(str_pk) != 0) {
    // failed to send PK
    return -1;
  }

  // create shared secret with servers PK and our SK
  unsigned char ss[crypto_box_BEFORENMBYTES];
  if(crypto_box_beforenm(ss, recv_pk, sk) != 0) {
    // shared secret creation failed
    return -1;
  }

  SetState(new SecureSocketHandler(ss));

  return 0;
}

int ServerConnection::SendMessage(std::string &plaintext) {
  std::unique_ptr<Message> message;
  if (Deserialize(message, plaintext, 0) != 0) {
    // failed to deserialize plaintext
    return -1;
  }

  return socket_handler->Send(sockfd, message);
}

std::unique_ptr<Message> ServerConnection::ReadMessage() {
  std::string plaintext = socket_handler->Recv(sockfd);

  std::unique_ptr<Message> message;
  if (Deserialize(message, plaintext, 1) != 0) {
    // failed to deserialize plaintext
    return std::make_unique(server_stream_in::Error("invalid payload message type"));
  }
  
  return message;
}