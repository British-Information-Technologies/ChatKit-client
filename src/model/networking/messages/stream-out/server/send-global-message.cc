#include <string>
#include <format>

#include "send-global-message.h"

using namespace server_stream_out;

SendGlobalMessage::SendGlobalMessage(std::string content) {
    this->type = kSendGlobalMessage;
    this->content = content;
}

std::string SendGlobalMessage::Serialize() {
    return std::format(R"({ "type": {}, "content": {} })", type, content);
}