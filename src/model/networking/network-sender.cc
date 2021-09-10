
#include "network-sender.h"

#include "connection-factory.h"

using namespace networking;
using namespace model_networking;
using namespace std;

NetworkSender::~NetworkSender() { connections->clear(); }

std::shared_ptr<
    std::unordered_map<int, std::shared_ptr<networking::Connection>>>
NetworkSender::get_connections() {
  return connections;
}

void NetworkSender::try_create_connection(const std::string &ip_address,
                                          const std::string &port) {
  ConnectionFactory factory;
  auto new_connection = factory.GetConnection(0, ip_address, port);

  int sockfd = new_connection->create_connection();
  if (sockfd < 0) {
    return;
  }

  pair<int, shared_ptr<Connection>> connection_pair(sockfd, new_connection);

  connections->insert(connection_pair);
}

int NetworkSender::send_message(const int &id, string &message) {
  if (connections->contains(id)) {
    shared_ptr<Connection> connection = connections->at(id);

    int sent_bytes = connection->send_message(message);

    return sent_bytes;
  }

  return 0;
}