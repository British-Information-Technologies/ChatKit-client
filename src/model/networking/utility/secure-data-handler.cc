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
  unsigned char nonce[crypto_box_NONCEBYTES + 1];
  randombytes_buf(nonce, crypto_box_NONCEBYTES);
  nonce[crypto_box_NONCEBYTES] = '\0';

  // encrypt message with shared secret
  unsigned long long data_len = data.length();
  unsigned char data_ptr[data_len + 1];
  strcpy((char*) data_ptr, data.c_str());
  
  unsigned long long ciphertext_len = crypto_box_MACBYTES + data_len;
  unsigned char ciphertext[ciphertext_len + 1];

  if (crypto_box_easy_afternm(
    ciphertext,
    data_ptr,
    data_len,
    nonce,
    ss.get()
  ) != 0) {
    // message encryption failed - KISS
    return "";
  }

  ciphertext[ciphertext_len] = '\0';

  // create packet
  std::string packet = json({
    {"payload", Bin2Base64(ciphertext)},
    {"nonce", Bin2Base64(nonce)}
  }).dump();

  // encode packet with base64
  return packet;
}

std::string SecureDataHandler::FormatRead(std::string &data) { 
  // check packet format
  json packet = json::parse(data);
  
  if (!packet.contains("nonce") || !packet.contains("payload")) {
    // invalid packet - network error
    return "";
  }

  // decode packet with base64
  unsigned char *nonce = Base642Bin(packet.at("nonce"));  

  unsigned char *ciphertext = Base642Bin(packet.at("payload"));  
  unsigned long long ciphertext_len = std::strlen((char*) ciphertext);

  // decrypt ciphertext with shared secret
  unsigned long long plaintext_len = ciphertext_len - crypto_box_MACBYTES;
  unsigned char plaintext[plaintext_len + 1];

  if (crypto_box_open_easy_afternm(
    plaintext,
    ciphertext,
    ciphertext_len,
    nonce,
    ss.get()
  ) != 0) {
    return "";
  }

  plaintext[plaintext_len] = '\0';

  free(nonce);
  free(ciphertext);
  
  // cast to string with length specified to avoid losing data from array conversion
  char plaintext_str[plaintext_len + 1];
  strcpy(plaintext_str, (char *) plaintext);

  return plaintext_str;
}
