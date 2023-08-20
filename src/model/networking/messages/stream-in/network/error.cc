#include <string>
#include <fmt/core.h>
#include <magic_enum.hpp>

#include "error.h"

using namespace network_stream_in;

Error::Error() {
    this->type = model::Type::Error;
}

std::string Error::Serialize() {
    return fmt::format("{{ \"type\": {} }}", magic_enum::enum_name(type));
}

model::StreamType Error::GetStreamType() {
    return model::StreamType::NetworkStreamIn;
}