#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <netdb.h>
#include <string>
#include <memory>
#include <algorithm>
#include <sodium.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <nlohmann/json.hpp>
#include "msd/channel.hpp"

#include "server-connection.h"

#include "messages/message.h"

#include "utility/secure-data-handler.h"

using namespace model;

using json = nlohmann::json;

int ServerConnection::GetRecipientPublicKey(unsigned char* recv_pk) {
  // read potential PK - todo
  // auto server_pk_msg = ReadMessage();
  
  // json server_pk_json = server_pk_msg->ToJson();

  // verify read message is a PK
  // if (!server_pk_json.contains("PublicKey")) {
    // read message is not a PK message
    // return -1;
  // }
  
  // extract PK -- TODO

  // verify PK with CA -- TODO

  // put server PK into output buffer for return use
  // *recv_pk = server_pk_json.at("PublicKey");

  return 0;
}

ServerConnection::ServerConnection(event_base *base,
                                   msd::channel<std::string> &network_manager_chann,
                                   const std::string &ip_address,
                                   const std::string &port)
    : Connection(base, network_manager_chann, ip_address, port) {
}

int ServerConnection::EstablishSecureConnection() {
  if (sodium_init() < 0) {
    // sodium initialisation failed
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

  // convert pk into message format
  std::string str_pk(reinterpret_cast<char const*>(pk), crypto_box_PUBLICKEYBYTES);
  std::unique_ptr<Message> msg_pk;
  if (DeserializeStreamOut(msg_pk.get(), str_pk) != 0) {
    // failed to create PK message
    return -1;
  }

  // send our PK as plaintext to server
  if (SendMessage(msg_pk.get()) != 0) {
    // failed to send PK
    return -1;
  }

  // create shared secret with servers PK and our SK
  unsigned char ss[crypto_box_BEFORENMBYTES];
  if(crypto_box_beforenm(ss, recv_pk, sk) != 0) {
    // shared secret creation failed
    return -1;
  }

  SetState(new SecureDataHandler(ss));

  return bufferevent_getfd(bev);
}