#include "connected.h"

#include <fmt/core.h>
#include <magic_enum.hpp>
#include <string>

using namespace server_stream_in;

Connected::Connected() {
    this->type = model::Type::Connected;
}

std::string Connected::Serialize() {
    return fmt::format(R"({{ "type": "{}" }})", magic_enum::enum_name(type));
}

model::StreamType Connected::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}