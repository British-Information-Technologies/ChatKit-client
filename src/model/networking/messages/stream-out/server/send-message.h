#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_SEND_MESSAGE_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_SEND_MESSAGE_H_

#include <string>

#include "./server-stream-out.h"

namespace server_stream_out {
    const std::string kSendMessage = "SendMessage";
    
    class SendMessage: public model::ServerStreamOut {
        private:
            std::string to;
            std::string content;

        public:
            SendMessage(std::string to, std::string content);

            std::string Serialize();
    };
}

#endif