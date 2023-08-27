#ifndef MODEL_NETWORKING_CLIENT_CONNECTION_H_
#define MODEL_NETWORKING_CLIENT_CONNECTION_H_

#include <memory>
#include <string>
#include "msd/channel.hpp"

#include "connection.h"

#include "model/networking/messages/message.h"
#include "utility/data.h"

namespace model {
    class ClientConnection : public Connection {
        private:
            int GetRecipientPublicKey(unsigned char* recv_pk);
            
            void ReadMessageCb();

        protected:
            ClientConnection(
                const std::string &uuid,
                std::shared_ptr<struct event_base> base,
                msd::channel<std::shared_ptr<Data>> &network_manager_chann,
                const std::string &ip_address,
                const std::string &port,
                unsigned char *pk,
                unsigned char *sk
            );

        public:
            static std::shared_ptr<Connection> Create(
                const std::string &uuid,
                std::shared_ptr<struct event_base> base,
                msd::channel<std::shared_ptr<Data>> &network_manager_chann,
                const std::string &ip_address,
                const std::string &port
            );
            
            int SendMessage(Message *message);
    };
}  // namespace model

#endif