#include <fmt/core.h>
#include <magic_enum.hpp>
#include <string>

#include "connecting.h"

using namespace network_stream_in;

Connecting::Connecting() {
    this->type = model::Type::Connecting;
}

std::string Connecting::Serialize() {
    return fmt::format(R"({{ "type": "{}" }})", magic_enum::enum_name(type));
}

model::StreamType Connecting::GetStreamType() {
    return model::StreamType::NetworkStreamIn;
}