#ifndef MODEL_NETWORKING_CLIENT_CONNECTION_H_
#define MODEL_NETWORKING_CLIENT_CONNECTION_H_

#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include "msd/channel.hpp"

#include "connection.h"

#include "model/networking/messages/message.h"

using json = nlohmann::json;

namespace model {
    class ClientConnection : public Connection {
        private:
            int GetRecipientPublicKey(unsigned char* recv_pk);

        public:
            ClientConnection(
                std::shared_ptr<struct event_base> base,
                msd::channel<json> &network_manager_chann,
                const std::string &ip_address,
                const std::string &port
            );
            
            int SendMessage(Message *message);
    };
}  // namespace model

#endif