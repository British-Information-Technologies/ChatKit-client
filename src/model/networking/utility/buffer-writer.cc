#include "buffer-writer.h"

#include <sys/socket.h>

using namespace model_networking_utility;

BufferWriter::BufferWriter(int sockfd) { this->sockfd = sockfd; }

int BufferWriter::write_line(std::string message) {
  message.push_back('\n');

  int sent_bytes = send(sockfd, message.c_str(), message.length(), 0);
  return sent_bytes;
}