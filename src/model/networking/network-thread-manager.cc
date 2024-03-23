#include "network-thread-manager.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include "messages/internal/event-error.h"
#include "messages/message.h"
#include "messages/stream-in/server/public-key.h"
#include "model/networking/connection/connection.h"
#include "model/networking/connection/tunnel/client-tunnel.h"
#include "model/networking/connection/tunnel/server-tunnel.h"
#include "model/networking/messages/stream-in/network/got-info.h"
#include "model/networking/messages/stream-in/server/connected-clients.h"
#include "model/networking/messages/stream-in/server/global-chat-messages.h"
#include "model/networking/messages/stream-out/network/connect.h"
#include "model/networking/messages/stream-out/network/info.h"
#include "model/networking/messages/stream-out/server/get-clients.h"
#include "model/networking/messages/stream-out/server/get-messages.h"

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
    std::cout << "[NetworkThreadManager]: input channel handler launched" << std::endl;

    // read incoming channel data from connection callbacks
    while (true) {
        auto data = buffer_reader->ReadData();

        if (!data.has_value()) {
            continue;
        }

        std::cout << "[NetworkManager]: recv channel data from sockfd " << data.value().sockfd << std::endl;

        auto end_point = connections.at(data->uuid);

        switch (data.value().message->GetType()) {
        case Type::Request: {
            switch (end_point->state) {
            case ConnectionState::NeedInfo: {
                network_stream_out::Info info = network_stream_out::Info();

                end_point->tunnel->SendMessage(&info);

                break;
            }

            case ConnectionState::GotInfo: {
                // todo: uuid, username should be loaded from some storage, currently random value
                boost::uuids::random_generator uuid_generator;
                boost::uuids::uuid uuid = uuid_generator();
                std::stringstream ss;
                ss << uuid;

                network_stream_out::Connect connect = network_stream_out::Connect(
                    ss.str(),
                    "mitch",
                    "111.111.111.111");

                end_point->tunnel->SendMessage(&connect);

                break;
            }

            default: {
            }
            }

            break;
        }

        case Type::GotInfo: {
            end_point->state = ConnectionState::GotInfo;

            network_stream_in::GotInfo* info = dynamic_cast<network_stream_in::GotInfo*>(data.value().message.get());

            // todo must check tunnel type but will be done with a refactor
            end_point->alias = info->GetServerAlias();
            end_point->name = info->GetServerOwner();

            end_point->observables->open_contents->Notify(end_point->alias, end_point->name);

            break;
        }

        case Type::Connecting: {
            end_point->state = ConnectionState::Connecting;

            end_point->observables->open_contents->Notify(end_point->alias, end_point->name);

            break;
        }

        case Type::Connected: {
            end_point->state = ConnectionState::Connected;

            // get clients and messages
            server_stream_out::GetClients get_clients = server_stream_out::GetClients();
            server_stream_out::GetMessages get_messages = server_stream_out::GetMessages();

            end_point->tunnel->SendMessage(&get_clients);
            end_point->tunnel->SendMessage(&get_messages);

            break;
        }

        case Type::ConnectedClients: {
            server_stream_in::ConnectedClients* connected_clients = dynamic_cast<server_stream_in::ConnectedClients*>(data.value().message.get());
            std::cout << "connected_clients: " << connected_clients->Serialize() << std::endl;
            //end_point->observables->connected_users->Notify();
        }

        case Type::GlobalChatMessages: {
            server_stream_in::GlobalChatMessages* client_messages = dynamic_cast<server_stream_in::GlobalChatMessages*>(data.value().message.get());
            std::cout << "client_messages: " << client_messages->Serialize() << std::endl;
            //end_point->observables->messages->Notify();
        }

        case Type::GlobalMessage: {
        }

        case Type::PublicKey: {
            server_stream_in::PublicKey* recv_pk = dynamic_cast<server_stream_in::PublicKey*>(data.value().message.get());

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