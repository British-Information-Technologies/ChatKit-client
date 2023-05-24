#include <string>
#include <format>

#include "connecting.h"

using namespace network_stream_in;

Connecting::Connecting() {
    this->type = kConnecting;
}

std::string Connecting::Serialize() {
    return std::format(R"({ "type": {} })", type);
}