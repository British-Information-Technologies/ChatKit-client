#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_GLOBAL_CHAT_MESSAGES_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_GLOBAL_CHAT_MESSAGES_H_

#include "./server-stream-in.h"

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

namespace server_stream_in {
    const std::string kGlobalChatMessages = "GlobalChatMessages";
    
    class GlobalChatMessages: public model::ServerStreamIn {
        private:
            json messages;

        public:
            GlobalChatMessages(json messages);

            std::string Serialize();
            
            model::StreamType GetStreamType();
    };
}

#endif