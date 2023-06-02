#ifndef MODEL_NETWORKING_UTILITY_BUFFER_WRITER_H_
#define MODEL_NETWORKING_UTILITY_BUFFER_WRITER_H_

#include <memory>
#include <string>
#include <event2/bufferevent.h>

namespace model {
  int WriteBufferLine(std::shared_ptr<struct bufferevent> bev, std::string message);
}  // namespace model_networking_utility

#endif