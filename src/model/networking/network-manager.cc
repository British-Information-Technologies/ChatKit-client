#include <sodium.h>
#include <string>
#include <unordered_map>
#include <memory>

#include "network-manager.h"
#include "connection-factory.h"

using namespace model;

NetworkManager::NetworkManager() {
  this->connection_factory = std::make_unique<ConnectionFactory>();
}

NetworkManager::~NetworkManager() {
  connections.clear();
}

std::unordered_map<int, std::shared_ptr<Connection>>
NetworkManager::GetConnections() {
  return connections;
}

void NetworkManager::TryCreateConnection(const int &type,
                                        const std::string &ip_address,
                                        const std::string &port) {
  if (sodium_init() < 0) {
    /* panic! library wont initilise */
    return;
  }

  auto new_connection = connection_factory->GetConnection(type, ip_address, port);

  if (new_connection->EstablishSecureConnection() != 0) {
    // panic! failed to create a secure connection
    return;
  }

  // todo -- magic number for faking purposes
  std::pair<int, std::shared_ptr<Connection>> connection_pair(1, new_connection);

  connections.insert(connection_pair);
}

int NetworkManager::SendMessage(const int &id, std::string &message) {
  if (connections.contains(id)) {
    std::shared_ptr<Connection> connection = connections.at(id);

    int sent_bytes = connection->SendMessage(message);

    return sent_bytes;
  }

  return 0;
}