#ifndef MODEL_NETWORKING_UTILITY_BUFFER_WRITER_H_
#define MODEL_NETWORKING_UTILITY_BUFFER_WRITER_H_

#include <string>
#include <event2/bufferevent.h>

namespace model {
  int WriteBufferLine(struct bufferevent *bev, std::string message);
}  // namespace model_networking_utility

#endif