#ifndef MODEL_NETWORKING_CONNECTION_TUNNEL_SERVER_H_
#define MODEL_NETWORKING_CONNECTION_TUNNEL_SERVER_H_

#include "msd/channel.hpp"
#include <memory>
#include <string>

#include "tunnel.h"

#include "model/networking/messages/message.h"

namespace model {
class ServerTunnel : public Tunnel {
public:
    ServerTunnel(
        std::shared_ptr<Connection> connection,
        std::shared_ptr<struct event_base> base,
        const std::string& ip_address,
        const std::string& port);

    int SendMessage(Message* message);
};
} // namespace model

#endif