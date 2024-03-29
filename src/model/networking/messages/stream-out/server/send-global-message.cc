#include <fmt/core.h>
#include <magic_enum.hpp>
#include <string>

#include "send-global-message.h"

using namespace server_stream_out;

SendGlobalMessage::SendGlobalMessage(const std::string& content) : content(content) {
    this->type = model::Type::SendGlobalMessage;
}

std::string SendGlobalMessage::Serialize() {
    return fmt::format(R"({{ "type": "{}", "content": "{}" }})", magic_enum::enum_name(type), content);
}

model::StreamType SendGlobalMessage::GetStreamType() {
    return model::StreamType::ServerStreamOut;
}