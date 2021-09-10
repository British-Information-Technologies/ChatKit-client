#include "socket-handler.h"

using namespace networking_utility;

SocketHandler::SocketHandler(int sockfd) {
  this->writer = new BufferWriter(sockfd);
}

SocketHandler::~SocketHandler() { delete writer; }