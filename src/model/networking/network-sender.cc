
#include "network-sender.h"

#include "connection-factory.h"

using namespace model_networking;
using namespace std;

NetworkSender::~NetworkSender() { connections.clear(); }

std::unordered_map<int, std::shared_ptr<Connection>>
NetworkSender::GetConnections() {
  return connections;
}

void NetworkSender::TryCreateConnection(const std::string &ip_address,
                                        const std::string &port) {
  ConnectionFactory factory;
  auto new_connection = factory.GetConnection(0, ip_address, port);

  int sockfd = new_connection->CreateConnection();
  if (sockfd < 0) {
    return;
  }

  pair<int, shared_ptr<Connection>> connection_pair(sockfd, new_connection);

  connections.insert(connection_pair);
}

int NetworkSender::SendMessage(const int &id, string &message) {
  if (connections.contains(id)) {
    shared_ptr<Connection> connection = connections.at(id);

    int sent_bytes = connection->SendMessage(message);

    return sent_bytes;
  }

  return 0;
}