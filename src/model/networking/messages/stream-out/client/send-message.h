#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_CLIENT_SEND_MESSAGE_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_CLIENT_SEND_MESSAGE_H_

#include <string>

#include "model/networking/messages/stream-out/client/client-stream-out.h"

namespace client_stream_out {
    const std::string kSendMessage = "SendMessage";
    
    class SendMessage: public model::ClientStreamOut {
        private:
            std::string time;
            std::string date;
            std::string content;

        public:
            SendMessage(
                std::string time,
                std::string date,
                std::string content
            );

            std::string Serialize();
    };
}

#endif