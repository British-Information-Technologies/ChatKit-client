#include "global-chat-messages.h"

#include <nlohmann/json.hpp>
#include <string>
#include <format>

using json = nlohmann::json;

using namespace server_stream_in;

GlobalChatMessages::GlobalChatMessages(json messages) {
    this->type = kGlobalChatMessages;
    this->messages = messages;
}

std::string GlobalChatMessages::Serialize() {
    return std::format(R"({ "type": {}, "messages": {} })", type, messages.dump());
}