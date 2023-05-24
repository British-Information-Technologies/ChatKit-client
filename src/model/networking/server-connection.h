#ifndef MODEL_NETWORKING_SERVER_CONNECTION_H_
#define MODEL_NETWORKING_SERVER_CONNECTION_H_

#include <memory>
#include <string>

#include "connection.h"
#include "messages/message.h"
#include "utility/socket-handler.h"

namespace model {
    class ServerConnection : public Connection {
        private:
            void SetState(SocketHandler *);
            
            int GetRecipientPublicKey(unsigned char* recv_pk);

        public:
            ServerConnection(const std::string &ip_address, const std::string &port);
            
            int EstablishSecureConnection();
            
            int SendMessage(std::string &);
            
            std::unique_ptr<Message> ReadMessage();
    };
}  // namespace model_networking_server

#endif