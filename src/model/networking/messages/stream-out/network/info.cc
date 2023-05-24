#include <string>
#include <format>

#include "info.h"

using namespace network_stream_out;

Info::Info() {
    this->type = kInfo;
}

std::string Info::Serialize() {
    return std::format(R"({ "type": {} })", type);
}