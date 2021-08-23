#include "insecure-socket-handler.h"

#include <nlohmann/json.hpp>

#include "base64.h"

using namespace networking_utility;
using json = nlohmann::json;

InsecureSocketHandler::InsecureSocketHandler(int sockfd)
    : SocketHandler(sockfd) {}

int InsecureSocketHandler::send(secure_string &plaintext) {
  if (plaintext.length() <= 0) return 0;

  plaintext.assign((std::string)EncodeBase64(plaintext));

  return writer->write_line((std::string)plaintext);
}

secure_string InsecureSocketHandler::recv() {
  secure_string payload = (secure_string)reader->read_line();

  payload.assign((std::string)DecodeBase64(payload));

  return payload;
}