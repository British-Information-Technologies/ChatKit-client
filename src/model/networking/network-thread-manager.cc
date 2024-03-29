#include "network-thread-manager.h"

#include <iostream>
#include <string>

#include "messages/internal/event-error.h"
#include "messages/message.h"
#include "messages/stream-in/server/public-key.h"

using namespace model;

NetworkThreadManager::NetworkThreadManager(
    std::unique_ptr<ChannelReader> buffer_reader) : buffer_reader(std::move(buffer_reader)) {}

NetworkThreadManager::~NetworkThreadManager() {
    connection_base_thread->request_stop();
    channel_thread->request_stop();
}

void NetworkThreadManager::LaunchConnectionBase(
    std::shared_ptr<event_base> connection_base) {
    // start event base loop for connection callbacks
    connection_base_thread = std::make_unique<std::jthread>(
        &NetworkThreadManager::LaunchConnectionBaseHandler,
        this,
        connection_base);
}

void NetworkThreadManager::LaunchInputChannel(
    std::unordered_map<std::string, std::shared_ptr<Connection>>& connections) {
    // start channel loop for reading incoming data from connection callbacks
    channel_thread = std::make_unique<std::jthread>(
        &NetworkThreadManager::LaunchInputChannelHandler,
        this,
        std::ref(connections));
}

void NetworkThreadManager::LaunchConnectionBaseHandler(
    std::shared_ptr<event_base> connection_base) {
    printf("[NetworkThreadManager]: connection base launched\n");
    event_base_loop(connection_base.get(), EVLOOP_NO_EXIT_ON_EMPTY);
    printf("[NetworkThreadManager]: connection base shutting down\n");
}

void NetworkThreadManager::LaunchInputChannelHandler(
    std::unordered_map<std::string, std::shared_ptr<Connection>>& connections) {
    std::cout << "[NetworkManager]: input channel handler launched" << std::endl;

    // read incoming channel data from connection callbacks
    while (true) {
        auto data = buffer_reader->ReadData();

        if (!data.has_value()) {
            continue;
        }

        std::cout << "[NetworkManager]: recv channel data from sockfd " << data.value().sockfd << std::endl;

        switch (data.value().message->GetType()) {
        case Type::PublicKey: {
            server_stream_in::PublicKey* recv_pk = dynamic_cast<server_stream_in::PublicKey*>(
                data.value().message.get());

            std::string end_point_uuid = recv_pk->GetFrom();

            auto end_point = connections.at(end_point_uuid);

            if (end_point->tunnel->IsSecure()) {
                std::cout << "[NetworkManager]: connection " << end_point_uuid << " already secure" << std::endl;
                continue;
            }

            auto pk = CreateServerStreamOutPublicKey(end_point_uuid, end_point->tunnel->GetPublicKey());

            // ask service connection to send our pk to end point connection
            connections.at(data.value().uuid)->tunnel->SendMessage(pk.get());

            // use received public key to create shared secret
            unsigned char* decode_pk = recv_pk->GetKey();

            if (end_point->tunnel->EstablishSecureTunnel(
                    end_point->listener->IsListening() ? Party::One : Party::Two,
                    decode_pk)
                != 0) {
                std::cout << "[NetworkManager]: secure connection with " << end_point_uuid << " failed" << std::endl;
                free(decode_pk);

                // panic! failed to create secure connection
                continue;
            }

            free(decode_pk);
            std::cout << "[NetworkManager]: secure connection with " << end_point_uuid << " established" << std::endl;
            break;
        }

        case Type::EventError: {
            std::unique_ptr<internal::EventError> err(dynamic_cast<internal::EventError*>(
                data.value().message.get()));

            std::cout << "[NetworkManager]: EventError msg " << err->GetMsg() << std::endl;
            break;
        }

        default: {
        }
        }
    }

    std::cout << "[NetworkManager]: input channel handler shutting down" << std::endl;
}