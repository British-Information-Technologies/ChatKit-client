#include <string>
#include <fmt/core.h>

#include "error.h"

using namespace network_stream_in;

Error::Error() {
    this->type = kError;
}

std::string Error::Serialize() {
    return fmt::format("{{ \"type\": {} }}", type);
}

model::StreamType Error::GetStreamType() {
    return model::StreamType::NetworkStreamIn;
}