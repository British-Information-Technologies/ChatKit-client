#include "disconnected.h"

#include <fmt/core.h>
#include <magic_enum.hpp>
#include <string>

using namespace server_stream_in;

Disconnected::Disconnected() {
    this->type = model::Type::Disconnected;
}

std::string Disconnected::Serialize() {
    return fmt::format(R"({{ "type": "{}" }})", magic_enum::enum_name(type));
}

model::StreamType Disconnected::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}