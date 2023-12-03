#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_GLOBAL_MESSAGE_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_GLOBAL_MESSAGE_H_

#include "./server-stream-in.h"

#include <string>

namespace server_stream_in {
class GlobalMessage : public model::ServerStreamIn {
private:
    const std::string from;
    const std::string content;

public:
    GlobalMessage(const std::string& from, const std::string& content);

    std::string Serialize();

    model::StreamType GetStreamType();
};
} // namespace server_stream_in

#endif