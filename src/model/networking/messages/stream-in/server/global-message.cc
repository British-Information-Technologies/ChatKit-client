#include "global-message.h"

#include <string>
#include <fmt/core.h>

using namespace server_stream_in;

GlobalMessage::GlobalMessage(std::string from, std::string content) {
    this->type = kGlobalMessage;
    this->from = from;
    this->content = content;
}

std::string GlobalMessage::Serialize() {
    return fmt::format("{{ \"type\": {}, \"from\": {}, \"content\": {} }}", type, from, content);
}
