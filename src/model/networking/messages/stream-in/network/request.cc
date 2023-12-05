#include <fmt/core.h>
#include <magic_enum.hpp>
#include <string>

#include "request.h"

using namespace network_stream_in;

Request::Request() {
    this->type = model::Type::Request;
}

std::string Request::Serialize() {
    return fmt::format(R"({{ "type": "{}" }})", magic_enum::enum_name(type));
}

model::StreamType Request::GetStreamType() {
    return model::StreamType::NetworkStreamIn;
}