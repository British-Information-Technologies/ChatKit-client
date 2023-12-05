#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_CLIENT_SEND_MESSAGE_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_CLIENT_SEND_MESSAGE_H_

#include <string>

#include "model/networking/messages/stream-in/client/client-stream-in.h"

namespace client_stream_in {
class SendMessage : public model::ClientStreamIn {
private:
    const std::string time;
    const std::string date;
    const std::string content;

public:
    SendMessage(
        const std::string& time,
        const std::string& date,
        const std::string& content);

    std::string Serialize();

    model::StreamType GetStreamType();
};
} // namespace client_stream_in

#endif