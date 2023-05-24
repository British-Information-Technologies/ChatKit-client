#include "secure-socket-handler.h"
#include "buffer-writer.h"
#include "buffer-reader.h"
#include "variants.h"

#include "../messages/message.h"
#include "../messages/stream-in/server/error.h"

#include <nlohmann/json.hpp>
#include <sodium.h>

using namespace model;

using json = nlohmann::json;

SecureSocketHandler::SecureSocketHandler(unsigned char *ss) {
  this->ss.reset(ss);
}

int SecureSocketHandler::Send(int sockfd, Message *message) {
  // create nonce
  unsigned char nonce[crypto_box_NONCEBYTES];
  randombytes_buf(nonce, sizeof nonce);  

  // encrypt message with shared secret
  const unsigned char* message_ptr = reinterpret_cast<const unsigned char*>(message->Serialize().c_str());
  unsigned long long message_len = sizeof message_ptr;
  
  unsigned long long ciphertext_len = crypto_box_MACBYTES + message_len;
  unsigned char ciphertext[ciphertext_len];
  if(crypto_box_easy_afternm(
    ciphertext,
    message_ptr,
    message_len,
    nonce,
    ss.get()
  ) != 0) {
    // message encryption failed
    return -1;
  }

  // create packet
  std::string packet = json({
    {"payload", std::string(reinterpret_cast<char const*>(ciphertext), ciphertext_len)},
    {"nonce", nonce}
  }).dump();

  // encode packet with base64
  const unsigned char* packet_ptr = reinterpret_cast<const unsigned char*>(packet.c_str());
  unsigned long long packet_len = sizeof packet_ptr;

  char encoded_packet[sodium_base64_ENCODED_LEN(packet_len, base64_VARIANT)];
  sodium_bin2base64(
    encoded_packet,
    sizeof encoded_packet,
    packet_ptr,
    packet_len,
    base64_VARIANT
  );

  // send encoded packet
  return WriteBufferLine(sockfd, encoded_packet);
}

std::string SecureSocketHandler::Recv(int sockfd) {
  // read encoded packet
  std::string encoded_packet = ReadBufferLine(sockfd);

  // decode packet with base64
  const char* encoded_packet_ptr = reinterpret_cast<const char*>(encoded_packet.c_str());

  size_t packet_len = encoded_packet.length() / 4 * 3; // base64 encodes 3 bytes as 4 characters
  unsigned char packet_ptr[packet_len];
  sodium_base642bin(
    packet_ptr,
    packet_len,
    encoded_packet_ptr,
    sizeof encoded_packet_ptr,
    NULL,
    &packet_len,
    NULL,
    base64_VARIANT
  );
  
  // check packet format
  json packet = json::parse(std::string(reinterpret_cast<char const*>(packet_ptr), packet_len));
  
  if (!packet.contains("nonce") || !packet.contains("payload")) {
    // invalid packet - network error
    return server_stream_in::Error("payload or nonce missing").Serialize();
  }

  // extract nonce from packet
  const unsigned char* nonce = reinterpret_cast<const unsigned char*>(std::string(packet.at("nonce")).c_str());

  // extract ciphertext from packet
  const unsigned char* ciphertext = reinterpret_cast<const unsigned char*>(std::string(packet.at("payload")).c_str());
  unsigned long long ciphertext_len = sizeof ciphertext;

  // decrypt ciphertext with shared secret
  unsigned long long plaintext_len = ciphertext_len - crypto_box_MACBYTES;
  unsigned char plaintext[plaintext_len];
  if(crypto_box_open_easy_afternm(
    plaintext,
    ciphertext,
    ciphertext_len,
    nonce,
    ss.get()
  ) != 0) {
    return server_stream_in::Error("decryption failed").Serialize();
  }
  
  // cast to string with length specified to avoid losing data from array conversion
  return std::string(reinterpret_cast<char const*>(plaintext), plaintext_len);
}
