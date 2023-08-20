#include "connected.h"

#include <string>
#include <fmt/core.h>
#include <magic_enum.hpp>

using namespace server_stream_in;

Connected::Connected() {
    this->type = model::Type::Connected;
}

std::string Connected::Serialize() {
    return fmt::format("{{ \"type\": {} }}", magic_enum::enum_name(type));
}

model::StreamType Connected::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}