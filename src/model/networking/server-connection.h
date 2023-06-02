#ifndef MODEL_NETWORKING_SERVER_CONNECTION_H_
#define MODEL_NETWORKING_SERVER_CONNECTION_H_

#include <string>
#include <event2/event.h>
#include "msd/channel.hpp"

#include "connection.h"

namespace model {
    class ServerConnection : public Connection {
        private:
            int GetRecipientPublicKey(unsigned char* recv_pk);

        public:
            ServerConnection(struct event_base *base, msd::channel<std::string> &network_manager_chann, const std::string &ip_address, const std::string &port);
            
            int EstablishSecureConnection();
    };
}  // namespace model_networking_server

#endif