#include "insecure-socket-handler.h"
#include "buffer-writer.h"
#include "buffer-reader.h"
#include "variants.h"

#include <nlohmann/json.hpp>
#include <sodium.h>

using namespace model_networking_utility;
using namespace model_message_functionality;
using json = nlohmann::json;

int InsecureSocketHandler::Send(int sockfd, Message* message) {
  // cannot send invalid messages
  std::string type = message->ToJson()["type"];
  if (type.compare(INVALID) == 0) return 0;
  
  // create packet
  std::string packet = json({
    {"payload", message->ToString()},
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
  return WriteBufferLine(sockfd, encoded_plaintext);
}

std::string InsecureSocketHandler::Recv(int sockfd) {
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
  
  if (!packet.contains("payload")) {
    // invalid packet
    return R"({"type": "Invalid"})";
  }

  // extract plaintext from packet
  const unsigned char* plaintext = reinterpret_cast<const unsigned char*>(std::string(packet.at("payload")).c_str());
  unsigned long long plaintext_len = sizeof plaintext;

  // cast to string with length specified to avoid losing data from array conversion
  return std::string(reinterpret_cast<char const*>(plaintext), plaintext_len);
}