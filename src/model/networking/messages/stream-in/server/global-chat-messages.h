#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_GLOBAL_CHAT_MESSAGES_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_GLOBAL_CHAT_MESSAGES_H_

#include "./server-stream-in.h"

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

namespace server_stream_in {
class GlobalChatMessages : public model::ServerStreamIn {
private:
    const json messages;

public:
    GlobalChatMessages(const json& messages);

    std::string Serialize();

    model::StreamType GetStreamType();
};
} // namespace server_stream_in

#endif