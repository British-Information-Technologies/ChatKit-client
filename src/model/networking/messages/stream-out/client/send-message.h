#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_CLIENT_SEND_MESSAGE_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_CLIENT_SEND_MESSAGE_H_

#include <string>

#include "model/networking/messages/stream-out/client/client-stream-out.h"

namespace client_stream_out {
    class SendMessage: public model::ClientStreamOut {
        private:
            const std::string time;
            const std::string date;
            const std::string content;

        public:
            SendMessage(
                const std::string &time,
                const std::string &date,
                const std::string &content
            );

            std::string Serialize();
            
            model::StreamType GetStreamType();
    };
}

#endif