#include "global-chat-messages.h"

#include <fmt/core.h>
#include <magic_enum.hpp>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

using namespace server_stream_in;

GlobalChatMessages::GlobalChatMessages(const json& messages) : messages(messages) {
    this->type = model::Type::GlobalChatMessages;
}

std::string GlobalChatMessages::Serialize() {
    return fmt::format(R"({{ "type": "{}", "messages": "{}" }})", magic_enum::enum_name(type), messages.dump());
}

model::StreamType GlobalChatMessages::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}