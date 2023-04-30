#include "buffer-reader.h"

#include <sys/socket.h>
#include <string>

std::string model_networking_utility::ReadBufferLine(int sockfd) {
  std::string payload;
  
  const int buffer_size = 1024;
  char buffer[buffer_size];
  
  int read_bytes = 0, read_index = 0;

  while (1) {
    read_bytes = recv(sockfd, buffer, buffer_size, 0);

    // create string from buffer data (if no data read ignore)
    if (read_bytes > 0) {
      for (; read_index < read_bytes; ++read_index) {
        char buffer_char = buffer[read_index];

        if (buffer_char == '\n') {
          return payload;
        } else {
          payload += buffer_char;
        }
      }

      read_index = 0;
      read_bytes = 0;
    } else if (read_bytes == -1) {
      // error - needs clean up code TODO
    }
  }
}