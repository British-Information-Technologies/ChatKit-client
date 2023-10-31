#include <string>
#include <event2/bufferevent.h>
#include <event2/buffer.h>

#include "buffer-reader.h"

std::string model::ReadBufferLine(bufferevent *bev) {
  std::string payload;
  
  const int buffer_size = 1024;
  char buffer[buffer_size];
  
  struct evbuffer *input = bufferevent_get_input(bev);
  
  // every message recieved is the length of the buffer (padded)
  int bytes_read;
  while ((bytes_read = evbuffer_remove(input, buffer, buffer_size)) > 0) {
    // create string from buffer
    payload.append(buffer, bytes_read);
  }

  return payload;
}