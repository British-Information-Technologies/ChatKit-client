#include "global-chat-messages.h"

#include <nlohmann/json.hpp>
#include <string>
#include <fmt/core.h>

using json = nlohmann::json;

using namespace server_stream_in;

GlobalChatMessages::GlobalChatMessages(json messages) {
    this->type = kGlobalChatMessages;
    this->messages = messages;
}

std::string GlobalChatMessages::Serialize() {
    return fmt::format("{{ \"type\": {}, \"messages\": {} }}", type, messages.dump());
}

model::StreamType GlobalChatMessages::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}