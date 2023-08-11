#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_CLIENT_SEND_MESSAGE_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_CLIENT_SEND_MESSAGE_H_

#include <string>

#include "model/networking/messages/stream-in/client/client-stream-in.h"

namespace client_stream_in {
    const std::string kSendMessage = "SendMessage";
    
    class SendMessage: public model::ClientStreamIn {
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
            
            model::StreamType GetStreamType();
    };
}

#endif