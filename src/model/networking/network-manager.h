#ifndef MODEL_NETWORKING_NETWORK_MANAGER_H_
#define MODEL_NETWORKING_NETWORK_MANAGER_H_

#include "msd/channel.hpp"
#include <event2/event.h>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>

#include "model/networking/connection/channel/channel-writer.h"
#include "model/networking/connection/connection.h"
#include "model/networking/messages/message.h"
#include "model/networking/network-thread-manager.h"
#include "model/networking/utility/data.h"
#include "view/observers/notifications/notification-observer.h"
#include "view/observers/server-observables.h"

namespace model {
class NetworkManager {
private:
    std::unique_ptr<NetworkThreadManager> thread_manager;

    std::shared_ptr<struct event_base> connection_base;

    std::shared_ptr<ChannelWriter> buffer_writer;

    std::unordered_map<std::string, std::shared_ptr<Connection>> connections;

public:
    NetworkManager(
        std::unique_ptr<NetworkThreadManager> thread_manager,
        std::shared_ptr<ChannelWriter> buffer_writer);
    ~NetworkManager();

    int SetNotification(const std::string& uuid, view::ServerObservables* observables);

    int EnableBuffer(const std::string& uuid);

    void LaunchConnectionManagement();

    void LaunchInputChannel();

    int LaunchListener(const std::string& uuid);

    int InitiateSecureConnection(const std::string& end_point_uuid, const std::string& service_uuid);

    int CreateConnection(
        const ConnectionType type,
        const std::string& uuid,
        const std::string& ip_address,
        const std::string& port);

    int SendMessage(const std::string& uuid, std::string& data);

    int SendClientMessage(
        const std::string& uuid,
        const std::string& time,
        const std::string& date,
        const std::string& data);
};
} // namespace model

#endif