#ifndef MODEL_NETWORKING_UTILITY_BUFFER_READER_H_
#define MODEL_NETWORKING_UTILITY_BUFFER_READER_H_

#include <string>

namespace model_networking_utility {
class BufferReader {
 private:
  int sockfd;

  const int buffer_size = 1024;
  char *input_buffer;
  int read_bytes;
  int read_index;

 public:
  BufferReader(int);

  ~BufferReader();

  std::string read_line();
};
}  // namespace model_networking_utility

#endif