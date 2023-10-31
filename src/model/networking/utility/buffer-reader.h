#ifndef MODEL_NETWORKING_UTILITY_BUFFER_READER_H_
#define MODEL_NETWORKING_UTILITY_BUFFER_READER_H_

#include <string>
#include <event2/bufferevent.h>

namespace model {
  std::string ReadBufferLine(struct bufferevent *bev);
}  // namespace model_networking_utility

#endif