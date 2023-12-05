#include <memory>
#include <string>

#include "network-model.h"

#include "networking/network-manager.h"

using namespace model;

NetworkModel::NetworkModel(
    std::shared_ptr<NetworkManager> network_manager) {
    this->network_manager = network_manager;
}

int NetworkModel::Run() {
    network_manager->LaunchConnectionBase();
    network_manager->LaunchInputChannel();

    CreateServiceServerConnection(); // TODO: move to connect on login and retry automatically if fail

    return 0;
}

int NetworkModel::CreateClientConnection(
    const std::string& uuid,
    const std::string& ip_address,
    const std::string& port) {
    if (network_manager->CreateConnection(
            ConnectionType::Client,
            uuid,
            ip_address,
            port)) {
        return -1;
    }

    /* TODO: Note: this is fake, the code will eventually be removed.
   * comment out when not testing, only use when testing (one 
   * client must listen). must comment out Initiate function call
   * inside CreateConnection and line below. */
    //if (network_manager->LaunchListener(uuid)) {
    //  return -1;
    //}
    // return 0;

    return network_manager->InitiateSecureConnection(uuid, /*TODO*/ "some higher hierarchy server");
}

int NetworkModel::CreateServerConnection(
    const std::string& uuid,
    const std::string& ip_address,
    const std::string& port) {
    if (network_manager->CreateConnection(
            ConnectionType::Server,
            uuid,
            ip_address,
            port)) {
        return -1;
    }

    return network_manager->InitiateSecureConnection(uuid, /*TODO*/ "some higher hierarchy server");
}

int NetworkModel::CreateServiceServerConnection() {
    // TODO: load ip addresses and ports (currently faked)
    const std::string uuid = "some higher hierarchy server";
    const std::string ip_address = "192.168.0.59";
    const std::string port = "5790";

    if (network_manager->CreateConnection(
            ConnectionType::Server,
            uuid,
            ip_address,
            port)) {
        return -1;
    }

    /* TODO: currently this connection will never recieve a pk to make it secure. 
   *       When done, it should ask some CA or something to verify it the pk
   *       it recieves.
   */
    return 0;
}

int NetworkModel::SendMessage(const std::string& uuid, std::string& data) {
    return network_manager->SendMessage(uuid, data);
}

int NetworkModel::SendClientMessage(
    const std::string& uuid,
    const std::string& time,
    const std::string& date,
    const std::string& data) {
    return network_manager->SendClientMessage(uuid, time, date, data);
}
