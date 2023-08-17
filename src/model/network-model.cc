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
  //TODO: if (network_manager->ConnectToServiceServer() != 0) {
    // failed to connect to service service
    //return -1;
  //}

  network_manager->LaunchConnectionBase();

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
  
  return network_manager->InitiateSecureConnection(uuid, /*TODO*/ "some higher hierarchy server");
}


int NetworkModel::CreateServerConnection(
  const std::string &uuid,
  const std::string &ip_address,
  const std::string &port
)
{
  if (network_manager->CreateConnection(
    ConnectionType::Server,
    uuid,
    ip_address,
    port
  )) {
    return -1;
  }

  return network_manager->InitiateSecureConnection(uuid, /*TODO*/ "some higher hierarchy server");
}

int NetworkModel::CreateServiceServerConnection() {
  // TODO: load ip addresses and ports (currently faked)
  const std::string uuid = "faked server uuid";
  const std::string ip_address = "localhost";
  const std::string port = "5790";

  if (network_manager->CreateConnection(
    ConnectionType::Server,
    uuid,
    ip_address,
    port
  )) {
    return -1;
  }
  
  /* TODO: currently this connection will immidately recieve a pk to make secure. 
           When done, it should ask some CA or something to verify it. */

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