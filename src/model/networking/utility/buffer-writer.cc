#include "buffer-writer.h"

#include <sys/socket.h>
#include <string>

int model_networking_utility::WriteBufferLine(int sockfd, std::string message) {
  message.push_back('\n');

  int sent_bytes = send(sockfd, message.c_str(), message.length(), 0);
  return sent_bytes;
}