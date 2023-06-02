#include "error.h"

#include <string>
#include <fmt/core.h>

using namespace server_stream_in;

Error::Error(std::string msg) {
    this->type = kError;
    this->msg = msg;
}

std::string Error::Serialize() {
    return fmt::format("{{ \"type\": {}, \"msg\": {} }}", type, msg);
}