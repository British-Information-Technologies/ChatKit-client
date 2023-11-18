#ifndef MODEL_NETWORKING_CONNECTION_H_
#define MODEL_NETWORKING_CONNECTION_H_

#include <memory>

#include "model/networking/connection/tunnel/tunnel.h"
#include "model/networking/connection/listener/event-listener.h"
#include "model/networking/connection/channel/channel-writer.h"

namespace model {
    enum class ConnectionType {
        Client,
        Server
    };

    struct Connection {
        std::unique_ptr<Tunnel> tunnel;
        std::unique_ptr<EventListener> listener;
        std::unique_ptr<ChannelWriter> channel;
    };
}

#endif