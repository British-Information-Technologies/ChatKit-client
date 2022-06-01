#include "socket-handler.h"

using namespace model_networking_utility;

SocketHandler::SocketHandler(int sockfd) {
  this->writer = new BufferWriter(sockfd);
}

SocketHandler::~SocketHandler() { delete writer; }