#include <string>
#include <fmt/core.h>
#include <magic_enum.hpp>

#include "get-messages.h"

using namespace server_stream_out;

GetMessages::GetMessages() {
    this->type = model::Type::GetMessages;
}

std::string GetMessages::Serialize() {
    return fmt::format(R"({{ "type": "{}" }})", magic_enum::enum_name(type));
}

model::StreamType GetMessages::GetStreamType() {
    return model::StreamType::ServerStreamOut;
}