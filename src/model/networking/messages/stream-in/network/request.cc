#include <string>
#include <fmt/core.h>

#include "request.h"

using namespace network_stream_in;

Request::Request() {
    this->type = kRequest;
}

std::string Request::Serialize() {
    return fmt::format("{{ \"type\": {} }}", type);
}