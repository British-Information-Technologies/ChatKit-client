#include "msd/channel.hpp"
#include <event2/event.h>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <sodium.h>
#include <string>
#include <thread>
#include <unordered_map>

#include "network-manager.h"

#include "messages/message.h"
#include "messages/stream-in/server/public-key.h"
#include "model/networking/connection/connection.h"
#include "model/networking/connection/injector.h"
#include "model/networking/connection/tunnel/tunnel-factory.h"
#include "network-manager.h"
#include "utility/data.h"

using namespace model;

NetworkManager::NetworkManager(
    std::unique_ptr<NetworkThreadManager> thread_manager,
    std::shared_ptr<ChannelWriter> buffer_writer)
    : thread_manager(std::move(thread_manager)), buffer_writer(buffer_writer) {
    connection_base.reset(event_base_new(),
                          [](event_base* b) {
                              event_base_loopexit(b, NULL);
                              event_base_free(b);
                          });
}

NetworkManager::~NetworkManager() {
    connections.clear();
}

void NetworkManager::LaunchConnectionManagement() {
    // start event base loop for connection callbacks
    thread_manager->LaunchConnectionBase(connection_base);
    // start channel loop for reading incoming data from connection callbacks
    thread_manager->LaunchInputChannel(connections);
}

int NetworkManager::LaunchListener(const std::string& uuid) {
    if (!connections.contains(uuid)) {
        printf("[NetworkManager]: connection does not exist\n");
        return -1;
    }

    auto conn = connections.at(uuid);

    printf("[NetworkManager]: starting connection listener\n");
    conn->listener->Listen();

    return 0;
}

int NetworkManager::InitiateSecureConnection(const std::string& end_point_uuid, const std::string& service_uuid) {
    if (!connections.contains(end_point_uuid) || !connections.contains(service_uuid)) {
        printf("[NetworkManager]: connections do not exist\n");
        return -1;
    }

    auto end_point = connections.at(end_point_uuid);

    if (end_point->tunnel->IsSecure()) {
        printf("[NetworkManager]: end point already secure\n");
        return -1;
    }

    auto service = connections.at(service_uuid);

    // TODO Note: comment out for python test server
    //if (!service->tunnel->IsSecure()) {
    //  printf("[NetworkManager]: service not secure\n");
    //  return -1;
    //}

    std::unique_ptr<Message> pk_msg = CreateServerStreamOutPublicKey(
        end_point_uuid,
        end_point->tunnel->GetPublicKey());

    // send our PK as plaintext
    if (service->tunnel->SendMessage(pk_msg.get()) < 0) {
        // failed to send PK
        printf("[NetworkManager]: failed to send public key\n");
        return -1;
    }

    return 0;
}

int NetworkManager::CreateConnection(
    const ConnectionType type,
    const std::string& uuid,
    const std::string& ip_address,
    const std::string& port) {
    if (connections.contains(uuid)) {
        printf("[NetworkManager]: connection loaded\n");
        return 0;
    }

    auto connection = Injector::inject_connection(
        type,
        uuid,
        connection_base,
        ip_address,
        port,
        buffer_writer);

    if (!connection) {
        printf("[NetworkManager]: connection failed to create\n");
        return -1;
    }

    if (connection->tunnel->Initiate()) {
        printf("[NetworkManager]: connection failed to initiate\n");
        return -1;
    }

    connections.insert(std::pair<std::string, std::shared_ptr<Connection>>(uuid, connection));

    printf("[NetworkManager]: connection created\n");
    return 0;
}

int NetworkManager::SendMessage(const std::string& uuid, std::string& data) {
    if (!connections.contains(uuid)) {
        return -1;
    }

    std::unique_ptr<Message> message(DeserializeStreamOut(data));

    int sent_bytes = connections.at(uuid)->tunnel->SendMessage(message.get());

    return sent_bytes;
}

int NetworkManager::SendClientMessage(
    const std::string& uuid,
    const std::string& time,
    const std::string& date,
    const std::string& data) {
    if (!connections.contains(uuid)) {
        return -1;
    }

    std::unique_ptr<Message> message = CreateClientStreamOutSendMessage(
        time,
        date,
        data);

    int sent_bytes = connections.at(uuid)->tunnel->SendMessage(message.get());

    return sent_bytes;
}