#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <sodium.h>
#include <event2/bufferevent.h>

#include "secure-data-handler.h"
#include "model/networking/utility/encode.h"
#include "model/networking/utility/decode.h"

using namespace model;

using json = nlohmann::json;

SecureDataHandler::SecureDataHandler(
  unsigned char *ss
): ss(ss) 
{}

DataHandlerType SecureDataHandler::GetType() {
  return type;
}

std::string SecureDataHandler::FormatSend(std::string &data) {
  // create nonce
  unsigned char nonce[crypto_box_NONCEBYTES];
  randombytes_buf(nonce, sizeof nonce);  

  // encrypt message with shared secret
  const unsigned char* data_ptr = reinterpret_cast<const unsigned char*>(data.c_str());
  unsigned long long data_len = sizeof data_ptr;
  
  unsigned long long ciphertext_len = crypto_box_MACBYTES + data_len;
  unsigned char ciphertext[ciphertext_len];
  if(crypto_box_easy_afternm(
    ciphertext,
    data_ptr,
    data_len,
    nonce,
    ss.get()
  ) != 0) {
    // message encryption failed - KISS
    return "";
  }

  // create packet
  std::string packet = json({
    {"payload", std::string(reinterpret_cast<char const*>(ciphertext), ciphertext_len)},
    {"nonce", nonce}
  }).dump();

  // encode packet with base64
  return Bin2Base64(packet);
}

std::string SecureDataHandler::FormatRead(std::string &data) {
  // decode packet with base64
  std::string packet_str = Base642Bin(data);
  
  // check packet format
  json packet = json::parse(packet_str);
  
  if (!packet.contains("nonce") || !packet.contains("payload")) {
    // invalid packet - network error
    return "";
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
    return "";
  }
  
  // cast to string with length specified to avoid losing data from array conversion
  return std::string(reinterpret_cast<char const*>(plaintext), plaintext_len);
}
