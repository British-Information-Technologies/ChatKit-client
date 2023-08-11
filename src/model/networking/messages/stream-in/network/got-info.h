#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_NETWORK_GOT_INFO_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_NETWORK_GOT_INFO_H_

#include <string>

#include "./network-stream-in.h"

namespace network_stream_in {
    const std::string kGotInfo = "GotInfo";
    
    class GotInfo: public model::NetworkStreamIn {
        private:
            std::string server_name;
            std::string server_owner;

        public:
            GotInfo(std::string server_name, std::string server_owner);

            std::string Serialize();
            
            model::StreamType GetStreamType();
    };
}

#endif