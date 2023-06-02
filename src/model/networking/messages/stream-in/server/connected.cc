#include "connected.h"

#include <string>
#include <fmt/core.h>

using namespace server_stream_in;

Connected::Connected() {
    this->type = kConnected;
}

std::string Connected::Serialize() {
    return fmt::format("{{ \"type\": {} }}", type);
}