#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_DISCONNECTED_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_DISCONNECTED_H_

#include "./server-stream-in.h"

#include <string>

namespace server_stream_in {
    const std::string kDisconnected = "Disconnected";
    
    class Disconnected: public model::ServerStreamIn {
        public:
            Disconnected();

            std::string Serialize();
    };
};

#endif