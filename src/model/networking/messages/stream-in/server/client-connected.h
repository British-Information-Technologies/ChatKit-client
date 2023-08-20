#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_CLIENT_CONNECTED_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_CLIENT_CONNECTED_H_

#include <string>

#include "./server-stream-in.h"

namespace server_stream_in {    
    class ClientConnected: public model::ServerStreamIn {
        private:
            const std::string id;
            const std::string username;
        
        public:
            ClientConnected(const std::string &id, const std::string &username);

            std::string Serialize();
            
            model::StreamType GetStreamType();
    };
}

#endif