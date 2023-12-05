#include <fmt/core.h>
#include <magic_enum.hpp>
#include <string>

#include "disconnect.h"

using namespace server_stream_out;

Disconnect::Disconnect() {
    this->type = model::Type::Disconnect;
}

std::string Disconnect::Serialize() {
    return fmt::format(R"({{ "type": "{}" }})", magic_enum::enum_name(type));
}

model::StreamType Disconnect::GetStreamType() {
    return model::StreamType::ServerStreamOut;
}