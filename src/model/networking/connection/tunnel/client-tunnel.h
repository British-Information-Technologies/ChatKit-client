#ifndef MODEL_NETWORKING_CONNECTION_TUNNEL_CLIENT_H_
#define MODEL_NETWORKING_CONNECTION_TUNNEL_CLIENT_H_

#include <memory>
#include <string>
#include "msd/channel.hpp"

#include "tunnel.h"

#include "model/networking/messages/message.h"

namespace model {
    class ClientTunnel : public Tunnel {
        protected:
            ClientTunnel(
                std::shared_ptr<Connection> connection,
                std::shared_ptr<struct event_base> base,
                const std::string &ip_address,
                const std::string &port,
                unsigned char *public_key,
                unsigned char *secret_key
            );

        public:
            static std::unique_ptr<Tunnel> Create(
                std::shared_ptr<Connection> connection,
                std::shared_ptr<struct event_base> base,
                const std::string &ip_address,
                const std::string &port
            );
            
            int SendMessage(Message *message);
    };
}  // namespace model

#endif