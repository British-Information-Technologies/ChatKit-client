#include <sodium.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <event2/event.h>
#include "msd/channel.hpp"

#include "network-manager.h"
#include "connection-factory.h"
#include "messages/message.h"

using namespace model;

NetworkManager::NetworkManager() {
  connection_base = event_base_new();
  connection_factory = std::make_unique<ConnectionFactory>();
}

NetworkManager::~NetworkManager() {
  event_base_loopexit(connection_base, NULL);
  event_base_free(connection_base);

  this->WaitForInternalThreadToExit();
  
  connections.clear();
}

void NetworkManager::Launch() {
  // todo - might be good as a coroutine

  // start event base loop for connection callbacks
  this->StartInternalThread();

  // read incoming channel data from connection callbacks
  for (const auto data: in_chann) { // blocks forever waiting for channel items
    printf("<data read from in_chann: %s>", data);

    std::unique_ptr<Message> message;
    if (DeserializeStreamIn(message.get(), data) != 0) {
      // failed to deserialize data
      continue;
    }

    // todo
  }
}

void NetworkManager::InternalThreadEntry() {
  event_base_loop(connection_base, EVLOOP_NO_EXIT_ON_EMPTY);
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

  auto new_connection = connection_factory->GetConnection(type, connection_base, std::ref(in_chann), ip_address, port);
  
  // create new connection event for the event base
  int sockfd = new_connection->EstablishSecureConnection();

  if (sockfd == -1) {
    // panic! failed to create secure connection
    return;
  }

  // store connection in map
  std::pair<int, std::shared_ptr<Connection>> connection_pair(sockfd, new_connection);

  connections.insert(connection_pair);
}

int NetworkManager::SendMessage(const int &id, std::string &data) {
  if (!connections.contains(id)) {
    return -1;
  }

  std::unique_ptr<Message> message;
  if (DeserializeStreamOut(message.get(), data) != 0) {
    return -1;
  }

  int sent_bytes = connections.at(id)->SendMessage(message.get());

  return sent_bytes;
}