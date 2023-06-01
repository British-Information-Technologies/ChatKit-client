#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_NETWORK_CONNECT_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_NETWORK_CONNECT_H_

#include <string>

#include "./network-stream-out.h"

namespace network_stream_out {
    const std::string kConnect = "Connect";
    
    class Connect: public model::NetworkStreamOut {
        private:
            std::string uuid;
            std::string username;
            std::string address;

        public:
            Connect(std::string uuid, std::string username, std::string address);

            std::string Serialize();
    };
}

#endif