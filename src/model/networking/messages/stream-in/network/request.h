#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_NETWORK_REQUEST_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_NETWORK_REQUEST_H_

#include <string>

#include "./network-stream-in.h"

namespace network_stream_in {
    const std::string kRequest = "Request";
    
    class Request: public NetworkStreamIn {
        public:
            Request();

            std::string Serialize();
    };
}

#endif