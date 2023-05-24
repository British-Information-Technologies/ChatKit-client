#include <string>
#include <format>

#include "request.h"

using namespace network_stream_in;

Request::Request() {
    this->type = kRequest;
}

std::string Request::Serialize() {
    return std::format(R"({ "type": {} })", type);
}