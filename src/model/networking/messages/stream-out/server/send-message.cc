#include <string>
#include <format>

#include "send-message.h"

using namespace server_stream_out;

SendMessage::SendMessage(std::string to, std::string content) {
    this->type = kSendMessage;
    this->to = to;
    this->content = content;
}

std::string SendMessage::Serialize() {
    return std::format(R"({ "type": {}, "to": {}, "content": {} })", type, to, content);
}