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

int ServerConnection::GetRecipientPublicKey(unsigned char* nonce) {
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
  if(crypto_box_keypair(pk, sk) != 0) {
    // keypair generation failed
    return -1;
  }

  // generate nonce
  unsigned char nonce[crypto_box_NONCEBYTES];
  randombytes_buf(nonce, sizeof nonce);

  // get B's public key -- todo
  if(GetRecipientPublicKey(nonce) != 0) {
    // failed to retrieve recipient public key
    return -1;
  }

  // create shared secret
  if(crypto_box_beforenm(ss, recv_pk, sk) != 0) {
    // shared secret creation failed
    return -1;
  }

  return 0;
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