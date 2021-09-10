#include "buffer-reader.h"

#include <sys/socket.h>

using namespace model_networking_utility;

BufferReader::BufferReader(int sockfd) {
  this->sockfd = sockfd;
  input_buffer = new char[buffer_size];
  read_bytes = 0;
  read_index = 0;
}

BufferReader::~BufferReader() { delete[] input_buffer; }

std::string BufferReader::read_line() {
  std::string payload;

  while (1) {
    if (read_index == 0 && read_bytes == 0) {
      // This may need a timeout just incase some error occurs
      read_bytes = recv(sockfd, input_buffer, buffer_size, 0);
    }

    if (read_bytes > 0) {
      for (; read_index < read_bytes; ++read_index) {
        char buffer_char = input_buffer[read_index];

        if (buffer_char == '\n') {
          ++read_index;
          return payload;
        } else {
          payload += buffer_char;
        }
      }

      read_index = 0;
      read_bytes = 0;
    } else {
      // Socket closed or socket error - needs clean up code
      return "socket close or socket error!";
    }
  }
}