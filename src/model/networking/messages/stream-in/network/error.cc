#include <string>
#include <format>

#include "error.h"

using namespace network_stream_in;

Error::Error() {
    this->type = kError;
}

std::string Error::Serialize() {
    return std::format(R"({ "type": {} })", type);
}