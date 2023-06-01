#include <string>
#include <memory>
#include <event2/event.h>
#include <msd/channel.hpp>

#include "connection-factory.h"

#include "server-connection.h"

using namespace model;

std::shared_ptr<Connection> ConnectionFactory::GetConnection(
  const int &type, struct event_base *base, msd::channel<std::string> *network_manager_chann, const std::string &ip_address, const std::string &port) {
    // if(type) return std::make_shared<ClientConnection>(ip_address, port); -- fake (todo)
    return std::make_shared<ServerConnection>(base, network_manager_chann, ip_address, port);
}