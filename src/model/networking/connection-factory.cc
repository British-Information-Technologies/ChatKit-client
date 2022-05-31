#include "connection-factory.h"

#include "server/server-connection.h"
#include "client/client-connection.h"

using namespace model_networking;
using namespace model_networking_server;
using namespace model_networking_client;

std::shared_ptr<model_networking::Connection> ConnectionFactory::GetConnection(
    const int &type, const std::string &ip_address, const std::string &port) {
      if(type) return std::make_shared<ClientConnection>(ip_address, port);
      
      return std::make_shared<ServerConnection>(ip_address, port);
}