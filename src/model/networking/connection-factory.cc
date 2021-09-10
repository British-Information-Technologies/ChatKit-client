#include "connection-factory.h"

#include "server/server-connection.h"

using namespace model_networking;
using namespace model_networking_server;

std::shared_ptr<model_networking::Connection> ConnectionFactory::GetConnection(
    const int &type, const std::string &ip_address, const std::string &port) {
  return std::make_shared<ServerConnection>(ip_address, port);
}