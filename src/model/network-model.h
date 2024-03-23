#ifndef MODEL_NETWORK_MODEL_H_
#define MODEL_NETWORK_MODEL_H_

#include <memory>
#include <string>

#include "networking/network-manager.h"
#include "view/observers/notifications/notification-observer.h"
#include "view/observers/server-observables.h"

namespace model {
class NetworkModel {
private:
    std::unique_ptr<NetworkManager> network_manager;

public:
    NetworkModel(
        std::unique_ptr<NetworkManager> network_manager);

    int Run();

    int SetNotification(const std::string& uuid, view::ServerObservables* notification);

    int EnableBuffer(const std::string& uuid);

    int CreateClientConnection(
        const std::string& uuid,
        const std::string& ip_address,
        const std::string& port);

    int CreateServerConnection(
        const std::string& uuid,
        const std::string& ip_address,
        const std::string& port);

    int CreateServiceConnection();

    int SendMessage(const std::string& uuid, std::string& data);

    int SendClientMessage(
        const std::string& uuid,
        const std::string& time,
        const std::string& date,
        const std::string& data);
};
} // namespace model

#endif