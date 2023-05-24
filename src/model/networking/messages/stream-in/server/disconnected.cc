#include "disconnected.h"

#include <string>
#include <format>

using namespace server_stream_in;

Disconnected::Disconnected() {
    this->type = kDisconnected;
}

std::string Disconnected::Serialize() {
    return std::format(R"({ "type": {} })", type);
}