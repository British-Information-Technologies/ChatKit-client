#include "cpp-chat-client/model/networking/connection.h"

using namespace model_networking;

Connection::Connection(const std::string &ip_address, const std::string &port) {
  socket_handler = nullptr;
  this->ip_address = ip_address;
  this->port = port;
}

Connection::~Connection() { delete socket_handler; }