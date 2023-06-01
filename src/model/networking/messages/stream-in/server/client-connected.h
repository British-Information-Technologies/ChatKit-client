#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_CLIENT_CONNECTED_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_CLIENT_CONNECTED_H_

#include <string>

#include "./server-stream-in.h"

namespace server_stream_in {
    const std::string kClientConnected = "ClientConnected";
    
    class ClientConnected: public model::ServerStreamIn {
        private:
            std::string id;
            std::string username;
        
        public:
            ClientConnected(std::string id, std::string username);

            std::string Serialize();
    };
};

#endif