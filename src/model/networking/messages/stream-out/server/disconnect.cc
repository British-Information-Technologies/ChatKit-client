#include <string>
#include <fmt/core.h>

#include "disconnect.h"

using namespace server_stream_out;

Disconnect::Disconnect() {
    this->type = kDisconnect;
}

std::string Disconnect::Serialize() {
    return fmt::format("{{ \"type\": {} }}", type);
}