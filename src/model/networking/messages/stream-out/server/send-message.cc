#include <fmt/core.h>
#include <magic_enum.hpp>
#include <string>

#include "send-message.h"

using namespace server_stream_out;

SendMessage::SendMessage(
    const std::string& to,
    const std::string& content) : to(to), content(content) {
    this->type = model::Type::SendMessage;
}

std::string SendMessage::Serialize() {
    return fmt::format(R"({{ "type": "{}", "to": "{}", "content": "{}" }})", magic_enum::enum_name(type), to, content);
}

model::StreamType SendMessage::GetStreamType() {
    return model::StreamType::ServerStreamOut;
}