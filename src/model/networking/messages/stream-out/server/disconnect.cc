#include <string>
#include <format>

#include "disconnect.h"

using namespace server_stream_out;

Disconnect::Disconnect() {
    this->type = kDisconnect;
}

std::string Disconnect::Serialize() {
    return std::format(R"({ "type": {} })", type);
}