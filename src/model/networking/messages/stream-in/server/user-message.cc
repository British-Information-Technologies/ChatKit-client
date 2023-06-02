#include "user-message.h"

#include <string>
#include <fmt/core.h>

using namespace server_stream_in;

UserMessage::UserMessage(std::string from, std::string content) {
    this->type = kUserMessage;
    this->from = from;
    this->content = content;
}

std::string UserMessage::Serialize() {
    return fmt::format("{{ \"type\": {}, \"from\": {}, \"content\": {} }}", type, from, content);
}
