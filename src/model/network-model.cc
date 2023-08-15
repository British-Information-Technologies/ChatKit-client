#include <memory>
#include <string>

#include "network-model.h"

#include "networking/network-manager.h"

using namespace model;

NetworkModel::NetworkModel(
  std::shared_ptr<NetworkManager> network_manager
) {
  this->network_manager = network_manager;
}

int NetworkModel::Run() {
  if (network_manager->ConnectToServiceServer() != 0) {
    // failed to connect to service service
    return -1;
  }

  network_manager->Launch();

  return 0;
}

int NetworkModel::CreateClientConnection(
  const std::string &uuid,
  const std::string &ip_address,
  const std::string &port
)
{
  if (network_manager->CreateConnection(
    ConnectionType::Client,
    uuid,
    ip_address,
    port
  )) {
    return -1;
  }
  
  // TODO: needs to communicate with server: network_manager->InitiateSecureConnection(uuid);

  return 0;
}

int NetworkModel::SendMessage(const std::string &uuid, std::string &data) {
  return network_manager->SendMessage(uuid, data);
}

int NetworkModel::SendClientMessage(
  const std::string &uuid,
  const std::string &time,
  const std::string &date,
  const std::string &data
)
{
  return network_manager->SendClientMessage(uuid, time, date, data);
}