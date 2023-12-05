#include "global-message.h"

#include <fmt/core.h>
#include <magic_enum.hpp>
#include <string>

using namespace server_stream_in;

GlobalMessage::GlobalMessage(const std::string& from, const std::string& content) : from(from), content(content) {
    this->type = model::Type::GlobalMessage;
}

std::string GlobalMessage::Serialize() {
    return fmt::format(R"({{ "type": "{}", "from": "{}", "content": "{}" }})", magic_enum::enum_name(type), from, content);
}

model::StreamType GlobalMessage::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}