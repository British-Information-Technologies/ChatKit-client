#include "connected.h"

#include <string>
#include <format>

using namespace server_stream_in;

Connected::Connected() {
    this->type = kConnected;
}

std::string Connected::Serialize() {
    return std::format(R"({ "type": {} })", type);
}