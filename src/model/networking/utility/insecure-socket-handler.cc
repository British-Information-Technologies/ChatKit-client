#include "insecure-socket-handler.h"

#include <nlohmann/json.hpp>
#include <sodium.h>

using namespace model_networking_utility;
using namespace model_message_functionality;
using json = nlohmann::json;

InsecureSocketHandler::InsecureSocketHandler(int sockfd)
    : SocketHandler(sockfd) {}

int InsecureSocketHandler::Send(Message* message) {
  std::string type = message->ToJson()["type"];
  if (type.compare(INVALID) == 0) return 0;

  // encode message with base64
  const unsigned char* message_ptr = reinterpret_cast<const unsigned char*>(message->ToString().c_str());

  int base64_variant = sodium_base64_VARIANT_ORIGINAL;
  char encoded_plaintext[sodium_base64_ENCODED_LEN(sizeof message_ptr, base64_variant)];
  sodium_bin2base64(
    encoded_plaintext,
    sizeof encoded_plaintext,
    message_ptr,
    sizeof message_ptr,
    base64_variant
  );

  // send plaintext message
  return writer->WriteLine(encoded_plaintext);
}

std::string InsecureSocketHandler::Recv() {
  return;
}