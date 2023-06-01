#include <string>
#include <nlohmann/json.hpp>
#include <sodium.h>
#include <event2/bufferevent.h>

#include "insecure-data-handler.h"
#include "variants.h"

using namespace model;

using json = nlohmann::json;

std::string InsecureDataHandler::FormatSend(std::string &data) {
  // create packet
  std::string packet = json({
    { "payload", data },
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

  return encoded_packet;
}

std::string InsecureDataHandler::FormatRead(std::string &data) {
  // decode packet with base64
  const char* data_ptr = reinterpret_cast<const char*>(data.c_str());

  size_t packet_len = data.length() / 4 * 3; // base64 encodes 3 bytes as 4 characters
  unsigned char packet_ptr[packet_len];
  sodium_base642bin(
    packet_ptr,
    packet_len,
    data_ptr,
    sizeof data_ptr,
    NULL,
    &packet_len,
    NULL,
    base64_VARIANT
  );
  
  // check packet format
  json packet = json::parse(std::string(reinterpret_cast<char const*>(packet_ptr), packet_len));
  
  if (!packet.contains("payload")) {
    // invalid packet, payload missing - KISS
    return "";
  }

  // extract plaintext from packet
  const unsigned char* plaintext = reinterpret_cast<const unsigned char*>(std::string(packet.at("payload")).c_str());
  unsigned long long plaintext_len = sizeof plaintext;

  // cast to string with length specified to avoid losing data from array conversion
  return std::string(reinterpret_cast<char const*>(plaintext), plaintext_len);
}