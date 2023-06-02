#include <string>
#include <fmt/core.h>

#include "info.h"

using namespace network_stream_out;

Info::Info() {
    this->type = kInfo;
}

std::string Info::Serialize() {
    return fmt::format("{{ \"type\": {} }}", type);
}