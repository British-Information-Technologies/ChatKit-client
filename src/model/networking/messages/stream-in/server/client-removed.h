#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_CLIENT_REMOVED_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_CLIENT_REMOVED_H_

#include <string>

#include "./server-stream-in.h"

namespace server_stream_in {
    const std::string kClientRemoved = "ClientRemoved";
    
    class ClientRemoved: public model::ServerStreamIn {
        private:
            std::string id;
        
        public:
            ClientRemoved(std::string id);

            std::string Serialize();
    };
};

#endif