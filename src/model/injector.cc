#include "injector.h"

#include "data-model.h"
#include "network-model.h"

#include "model/friend-functionality/friend-utility.h"
#include "model/networking/connection/channel/channel-reader.h"
#include "model/networking/connection/channel/channel-writer.h"
#include "model/networking/network-thread-manager.h"
#include "model/server-functionality/server-utility.h"

#include "networking/network-manager.h"

#include <iostream>

using namespace model;
using namespace model_friend_functionality;
using namespace model_server_functionality;

std::unique_ptr<DataModel> Injector::inject_data_model() {
    std::unique_ptr<FriendUtility> friend_api = std::make_unique<FriendUtility>();
    std::unique_ptr<ServerUtility> server_api = std::make_unique<ServerUtility>();

    std::unique_ptr<DataModel> data_model = std::make_unique<DataModel>(
        std::move(friend_api),
        std::move(server_api));

    return data_model;
}

// todo: create injection functions for different objects
std::unique_ptr<NetworkModel> Injector::inject_network_model() {
    std::shared_ptr<ChannelWriter> buffer_writer = std::make_shared<ChannelWriter>();
    std::unique_ptr<ChannelReader> buffer_reader = std::make_unique<ChannelReader>(buffer_writer->GetBuffer());

    std::unique_ptr<NetworkThreadManager> thread_manager = std::make_unique<NetworkThreadManager>(
        std::move(buffer_reader));

    std::unique_ptr<NetworkManager> network_manager = std::make_unique<NetworkManager>(
        std::move(thread_manager),
        buffer_writer);

    std::unique_ptr<NetworkModel> network_model = std::make_unique<NetworkModel>(
        std::move(network_manager));

    network_model->Run();

    return network_model;
}