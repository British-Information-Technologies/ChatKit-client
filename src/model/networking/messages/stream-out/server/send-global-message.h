#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_SEND_GLOBAL_MESSAGE_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_SEND_GLOBAL_MESSAGE_H_

#include <string>

#include "./server-stream-out.h"

namespace server_stream_out {
class SendGlobalMessage : public model::ServerStreamOut {
private:
    const std::string content;

public:
    SendGlobalMessage(const std::string& content);

    std::string Serialize();

    model::StreamType GetStreamType();
};
}// namespace server_stream_out

#endif