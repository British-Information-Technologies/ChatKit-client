#include <string>
#include <fmt/core.h>

#include "connecting.h"

using namespace network_stream_in;

Connecting::Connecting() {
    this->type = kConnecting;
}

std::string Connecting::Serialize() {
    return fmt::format("{{ \"type\": {} }}", type);
}

model::StreamType Connecting::GetStreamType() {
    return model::StreamType::NetworkStreamIn;
}