#ifndef MODEL_NETWORKING_UTILITY_BUFFER_WRITER_H_
#define MODEL_NETWORKING_UTILITY_BUFFER_WRITER_H_

#include <string>

namespace model {
  int WriteBufferLine(int sockfd, std::string message);
}  // namespace model_networking_utility

#endif