#include "server-connection.h"

#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <netdb.h>

#include <algorithm>
#include <nlohmann/json.hpp>
#include <sodium.h>

#include "../../message-functionality/client-stream-in-factory.h"
#include "../../message-functionality/client-stream-out-factory.h"
#include "../../message-functionality/network-stream-in-factory.h"
#include "../../message-functionality/network-stream-out-factory.h"
#include "../utility/insecure-socket-handler.h"
#include "../utility/secure-socket-handler.h"

using namespace model_networking_server;
using namespace model_message_functionality;
using namespace model_networking_utility;
using json = nlohmann::json;

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

int ServerConnection::GetRecipientPublicKey(unsigned char* recv_pk) {
  // read server PK
  auto server_pk_msg = ReadMessage();

  // verify PK with CA -- TODO

  return 0;
}

ServerConnection::ServerConnection(const std::string &ip_address,
                                   const std::string &port)
    : Connection(ip_address, port) {
  this->stream_out_factory = std::make_shared<NetworkStreamOutFactory>();
  this->stream_in_factory = std::make_shared<NetworkStreamInFactory>();
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
  std::unique_ptr<Message> message = stream_out_factory->GetMessage(plaintext);

  return socket_handler->Send(sockfd, message.get());
}

std::unique_ptr<Message> ServerConnection::ReadMessage() {
  std::string plaintext = socket_handler->Recv(sockfd);

  return stream_in_factory->GetMessage(plaintext);
}