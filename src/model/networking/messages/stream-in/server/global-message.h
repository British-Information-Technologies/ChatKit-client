#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_GLOBAL_MESSAGE_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_GLOBAL_MESSAGE_H_

#include "./server-stream-in.h"

#include <string>

namespace server_stream_in {
    const std::string kGlobalMessage = "GlobalMessage";
    
    class GlobalMessage: public model::ServerStreamIn {
        private:
            std::string from;
            std::string content;
        
        public:
            GlobalMessage(std::string from, std::string content);

            std::string Serialize();
            
            model::StreamType GetStreamType();
    };
}

#endif