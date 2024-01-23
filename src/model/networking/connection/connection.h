#ifndef MODEL_NETWORKING_CONNECTION_H_
#define MODEL_NETWORKING_CONNECTION_H_

#include <memory>

#include "model/networking/connection/channel/channel-writer.h"
#include "model/networking/connection/listener/event-listener.h"
#include "model/networking/connection/tunnel/tunnel.h"
#include "view/observers/notifications/notification-observer.h"

namespace model {
enum class ConnectionType {
    Client,
    Server
};

enum class ConnectionState {
    NeedInfo,
    GotInfo,
    Connecting,
    Connected
};

struct Connection {
    std::string uuid;
    std::string alias;
    std::string name;

    std::unique_ptr<view::NotificationObserver> notification;

    std::unique_ptr<Tunnel> tunnel;
    std::unique_ptr<EventListener> listener;
    std::shared_ptr<ChannelWriter> channel;

    ConnectionState state;
};
} // namespace model

#endif