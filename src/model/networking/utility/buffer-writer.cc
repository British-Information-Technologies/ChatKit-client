#include "buffer-writer.h"

#include <string>
#include <event2/bufferevent.h>

int model::WriteBufferLine(bufferevent *bev, std::string message) {
  message.push_back('\n');

  size_t len = message.length();
  if (bufferevent_write(bev, message.c_str(), len) != 0) {
    return -1;
  }

  return len;
}