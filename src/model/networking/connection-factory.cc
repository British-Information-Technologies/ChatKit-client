#include <string>
#include <memory>

#include "connection-factory.h"

#include "server-connection.h"

using namespace model;

std::shared_ptr<Connection> ConnectionFactory::GetConnection(
  const int &type, const std::string &ip_address, const std::string &port) {
    // if(type) return std::make_shared<ClientConnection>(ip_address, port); -- fake (todo)
    return std::make_shared<ServerConnection>(ip_address, port);
}