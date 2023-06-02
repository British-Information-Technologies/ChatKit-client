#include <string>
#include <fmt/core.h>

#include "send-message.h"

using namespace server_stream_out;

SendMessage::SendMessage(std::string to, std::string content) {
    this->type = kSendMessage;
    this->to = to;
    this->content = content;
}

std::string SendMessage::Serialize() {
    return fmt::format("{{ \"type\": {}, \"to\": {}, \"content\": {} }}", type, to, content);
}