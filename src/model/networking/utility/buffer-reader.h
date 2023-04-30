#ifndef MODEL_NETWORKING_UTILITY_BUFFER_READER_H_
#define MODEL_NETWORKING_UTILITY_BUFFER_READER_H_

#include <string>

namespace model_networking_utility {
  std::string ReadBufferLine(int sockfd);
}  // namespace model_networking_utility

#endif