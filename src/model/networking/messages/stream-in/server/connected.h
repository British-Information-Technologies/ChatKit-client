#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_CONNECTED_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_CONNECTED_H_

#include "./server-stream-in.h"

#include <string>

namespace server_stream_in {    
    class Connected: public model::ServerStreamIn {
        public:
            Connected();

            std::string Serialize();
            
            model::StreamType GetStreamType();
    };
}

#endif