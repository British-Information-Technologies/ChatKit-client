#include "injector.h"

#include "data-model.h"
#include "network-model.h"

#include "friend-functionality/friend-utility.h"
#include "server-functionality/server-utility.h"

#include "networking/network-manager.h"

using namespace model;
using namespace model_friend_functionality;
using namespace model_server_functionality;

std::shared_ptr<DataModel> Injector::inject_data_model() {
    std::shared_ptr<FriendUtility> friend_api;
    std::shared_ptr<ServerUtility> server_api;

    std::shared_ptr<DataModel> data_model(
      new DataModel(
        friend_api,
        server_api
      )
    );

    return data_model;
}

std::shared_ptr<NetworkModel> Injector::inject_network_model() {
  std::shared_ptr<NetworkManager> network_manager(new NetworkManager());
  
  std::shared_ptr<NetworkModel> network_model(
    new NetworkModel(
      network_manager
    )
  );

  return network_model;
}