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
  int res = network_manager->CreateConnection(
    ConnectionType::Client,
    uuid,
    ip_address,
    port
  );
  
  if (res == -1) {
    printf("[Connection]: failed to initiate\n");
    return -1;

  } else if (res == 1) {
    printf("[Connection]: loaded\n");
    return 0;
  }

  printf("[Connection]: created\n");

  network_manager->InitiateSecureConnection(uuid);

  printf("[Connection]: public key transmitted");

  return 0;
}

int NetworkModel::SendMessage(const std::string &uuid, std::string &data) {
  return network_manager->SendMessage(uuid, data);
}