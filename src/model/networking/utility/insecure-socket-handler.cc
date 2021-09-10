#include "insecure-socket-handler.h"

#include <nlohmann/json.hpp>

#include "base64.h"

using namespace model_networking_utility;
using namespace model_message_functionality;
using json = nlohmann::json;

InsecureSocketHandler::InsecureSocketHandler(int sockfd)
    : SocketHandler(sockfd) {}

int InsecureSocketHandler::send(Message* message) {
  std::string type = message->ToJson()["type"];

  if (type.compare(INVALID) == 0) return 0;

  std::string json_string = message->ToString();

  std::string encoded_plaintext = EncodeBase64(json_string);

  return writer->write_line(encoded_plaintext);
}

std::string InsecureSocketHandler::recv(std::string& payload) {
  payload.assign(DecodeBase64(payload));

  return payload;
}