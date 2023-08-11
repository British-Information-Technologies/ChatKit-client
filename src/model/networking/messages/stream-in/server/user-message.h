#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_USER_MESSAGE_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_USER_MESSAGE_H_

#include "./server-stream-in.h"

#include <string>

namespace server_stream_in {
    const std::string kUserMessage = "UserMessage";
    
    class UserMessage: public model::ServerStreamIn {
        private:
            std::string from;
            std::string content;

        public:
            UserMessage(std::string from, std::string content);

            std::string Serialize();
            
            model::StreamType GetStreamType();
    };
}

#endif