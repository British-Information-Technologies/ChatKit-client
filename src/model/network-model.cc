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

int NetworkModel::SendMessage(const int& id, std::string& message) {
  return network_manager->SendMessage(id, message);
}