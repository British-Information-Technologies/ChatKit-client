#include <fmt/core.h>
#include <magic_enum.hpp>
#include <string>

#include "info.h"

using namespace network_stream_out;

Info::Info() {
    this->type = model::Type::Info;
}

std::string Info::Serialize() {
    return fmt::format(R"({{ "type": "{}" }})", magic_enum::enum_name(type));
}

model::StreamType Info::GetStreamType() {
    return model::StreamType::NetworkStreamOut;
}