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

namespace {
  struct Packet {
      std::string nonce;
      std::string payload;
  };

  void to_json(json &j, const Packet &p) {
      j = json{{"nonce", p.nonce}, {"payload", p.payload}};
  }

  void from_json(const json &j, Packet &p) {
      j.at("nonce").get_to(p.nonce);
      j.at("payload").get_to(p.payload);
  }
} // namespace

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
  randombytes_buf(nonce, crypto_box_NONCEBYTES);

  // encrypt message with shared secret
  unsigned long long data_len = data.length();
  unsigned char data_ptr[data_len + 1];
  strcpy((char*) data_ptr, data.c_str());
  
  unsigned long long ciphertext_len = crypto_box_MACBYTES + data_len;
  unsigned char ciphertext[ciphertext_len];

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

  // create packet
  json packet = Packet { Bin2Base64(nonce, crypto_box_NONCEBYTES), Bin2Base64(ciphertext, ciphertext_len) };

  // encode packet with base64
  return packet.dump();
}

std::string SecureDataHandler::FormatRead(std::string &data) {
  try {
    // check packet format
    auto packet = json::parse(data).template get<Packet>();

    // decode packet with base64
    auto [nonce, _] = Base642Bin(packet.nonce);

    auto [ciphertext, ciphertext_len] = Base642Bin(packet.payload);
    
    // decrypt ciphertext with shared secret
    unsigned long long plaintext_len = ciphertext_len - crypto_box_MACBYTES;
    unsigned char plaintext[plaintext_len];

    if (int a = crypto_box_open_easy_afternm(
      plaintext,
      ciphertext,
      ciphertext_len,
      nonce,
      ss.get()
    ) != 0) {
      free(nonce);
      free(ciphertext);
      
      return "";
    }

    free(nonce);
    free(ciphertext);
    
    // cast to string with length specified to avoid losing data from array conversion
    return std::string((char*) plaintext, plaintext_len);

  } catch (std::exception _) {
    // invalid packet - KISS
    return "";
  }
}
