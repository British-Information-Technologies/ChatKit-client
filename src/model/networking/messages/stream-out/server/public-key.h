#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_PUBLIC_KEY_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_PUBLIC_KEY_H_

#include "./server-stream-out.h"

#include <string>

namespace server_stream_out {
    class PublicKey: public model::ServerStreamOut {
        private:
            const std::string to;
            const std::string key;
        
        public:
            PublicKey(const std::string &to, const std::string &key);

            std::string Serialize();

            unsigned char* GetKey();
            
            model::StreamType GetStreamType();
    };
}

#endif