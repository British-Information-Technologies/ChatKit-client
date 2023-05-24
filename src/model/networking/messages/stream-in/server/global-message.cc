#include "global-message.h"

#include <string>
#include <format>

using namespace server_stream_in;

GlobalMessage::GlobalMessage(std::string from, std::string content) {
    this->type = kGlobalMessage;
    this->from = from;
    this->content = content;
}

std::string GlobalMessage::Serialize() {
    return std::format(R"({ "type": {}, "from": {}, "content": {} })", type, from, content);
}
