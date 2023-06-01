#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_NETWORK_CONNECTING_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_NETWORK_CONNECTING_H_

#include <string>

#include "./network-stream-in.h"

namespace network_stream_in {
    const std::string kConnecting = "Connecting";

    class Connecting: public model::NetworkStreamIn {
        public:
            Connecting();

            std::string Serialize();
    };
}

#endif