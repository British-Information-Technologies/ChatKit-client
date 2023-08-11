#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_PUBLIC_KEY_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_PUBLIC_KEY_H_

#include "./server-stream-in.h"

#include <string>

namespace server_stream_in {
    const std::string kPublicKey = "PublicKey";
    
    class PublicKey: public model::ServerStreamIn {
        private:
            std::string key;
        
        public:
            PublicKey(std::string key);

            std::string Serialize();

            std::string GetKey();
            
            model::StreamType GetStreamType();
    };
}

#endif