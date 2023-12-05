#ifndef MODEL_NETWORKING_UTILITY_BUFFER_READER_H_
#define MODEL_NETWORKING_UTILITY_BUFFER_READER_H_

#include <event2/bufferevent.h>
#include <string>

namespace model {
std::string ReadBufferLine(struct bufferevent* bev);
} // namespace model

#endif