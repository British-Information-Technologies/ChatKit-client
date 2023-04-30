#include "insecure-socket-handler.h"
#include "buffer-writer.h"
#include "buffer-reader.h"

#include <nlohmann/json.hpp>
#include <sodium.h>

using namespace model_networking_utility;
using namespace model_message_functionality;
using json = nlohmann::json;

#define base64_VARIANT sodium_base64_VARIANT_ORIGINAL

int InsecureSocketHandler::Send(int sockfd, Message* message) {
  std::string type = message->ToJson()["type"];
  if (type.compare(INVALID) == 0) return 0;

  // encode message with base64
  const unsigned char* message_ptr = reinterpret_cast<const unsigned char*>(message->ToString().c_str());

  char encoded_plaintext[sodium_base64_ENCODED_LEN(sizeof message_ptr, base64_VARIANT)];
  sodium_bin2base64(
    encoded_plaintext,
    sizeof encoded_plaintext,
    message_ptr,
    sizeof message_ptr,
    base64_VARIANT
  );

  // send plaintext message
  return WriteBufferLine(sockfd, encoded_plaintext);
}

std::string InsecureSocketHandler::Recv(int sockfd) {
  // read base64 encoded message
  std::string payload = ReadBufferLine(sockfd);

  // decode message with base64
  const char* payload_ptr = reinterpret_cast<const char*>(payload.c_str());

  size_t plaintext_len = payload.length() / 4 * 3; // base64 encodes 3 bytes as 4 characters
  unsigned char plaintext[plaintext_len];
  sodium_base642bin(
    plaintext,
    plaintext_len,
    payload_ptr,
    sizeof payload_ptr,
    NULL,
    &plaintext_len,
    NULL,
    base64_VARIANT
  );

  return reinterpret_cast<char const*>(plaintext);
}