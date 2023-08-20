#include <string>
#include <fmt/core.h>
#include <magic_enum.hpp>

#include "request.h"

using namespace network_stream_in;

Request::Request() {
    this->type = model::Type::Request;
}

std::string Request::Serialize() {
    return fmt::format("{{ \"type\": {} }}", magic_enum::enum_name(type));
}

model::StreamType Request::GetStreamType() {
    return model::StreamType::NetworkStreamIn;
}