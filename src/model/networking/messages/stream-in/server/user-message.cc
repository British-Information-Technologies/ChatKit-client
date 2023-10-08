#include "user-message.h"

#include <string>
#include <fmt/core.h>
#include <magic_enum.hpp>

using namespace server_stream_in;

UserMessage::UserMessage(const std::string &from, const std::string &content): from(from), content(content) {
    this->type = model::Type::UserMessage;
}

std::string UserMessage::Serialize() {
    return fmt::format(R"({{ "type": "{}", "from": "{}", "content": "{}" }})", magic_enum::enum_name(type), from, content);
}

model::StreamType UserMessage::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}