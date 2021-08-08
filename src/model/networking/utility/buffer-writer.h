#ifndef CPPCHATCLIENT_BUFFER_WRITER_H_
#define CPPCHATCLIENT_BUFFER_WRITER_H_

#include <string>

namespace networking_utility {
class BufferWriter {
 private:
  int sockfd;

 public:
  BufferWriter(int);

  int write_line(std::string);
};
}  // namespace networking_utility

#endif