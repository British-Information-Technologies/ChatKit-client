#include "disconnected.h"

#include <string>
#include <fmt/core.h>

using namespace server_stream_in;

Disconnected::Disconnected() {
    this->type = kDisconnected;
}

std::string Disconnected::Serialize() {
    return fmt::format("{{ \"type\": {} }}", type);
}