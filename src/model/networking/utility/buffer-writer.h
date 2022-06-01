#ifndef MODEL_NETWORKING_UTILITY_BUFFER_WRITER_H_
#define MODEL_NETWORKING_UTILITY_BUFFER_WRITER_H_

#include <string>

namespace model_networking_utility {
class BufferWriter {
 private:
  int sockfd;

 public:
  BufferWriter(int);

  int WriteLine(std::string);
};
}  // namespace model_networking_utility

#endif