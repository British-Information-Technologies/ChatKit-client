#ifndef MODEL_NETWORKING_UTILITY_BUFFER_WRITER_H_
#define MODEL_NETWORKING_UTILITY_BUFFER_WRITER_H_

#include <event2/bufferevent.h>
#include <memory>
#include <string>

namespace model {
int WriteBufferLine(std::shared_ptr<struct bufferevent> bev, std::string message);
}// namespace model

#endif