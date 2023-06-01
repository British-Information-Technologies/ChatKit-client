#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_SEND_GLOBAL_MESSAGE_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_SEND_GLOBAL_MESSAGE_H_

#include <string>

#include "./server-stream-out.h"

namespace server_stream_out {
    const std::string kSendGlobalMessage = "SendGlobalMessage";
    
    class SendGlobalMessage: public model::ServerStreamOut {
        private:
            std::string content;

        public:
            SendGlobalMessage(std::string content);

            std::string Serialize();
    };
}

#endif