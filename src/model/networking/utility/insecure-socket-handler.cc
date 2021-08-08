#include "insecure-socket-handler.h"

#include <nlohmann/json.hpp>

using namespace networking_utility;
using json = nlohmann::json;

InsecureSocketHandler::InsecureSocketHandler(int sockfd)
    : SocketHandler(sockfd) {}

int InsecureSocketHandler::send(secure_string &plaintext) {
  if (plaintext.length() <= 0) return 0;

  return writer->write_line((std::string)plaintext);
}

secure_string InsecureSocketHandler::recv() {
  secure_string payload = (secure_string)reader->read_line();

  return payload;
}