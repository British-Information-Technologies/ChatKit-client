#include "error.h"

#include <string>
#include <format>

using namespace server_stream_in;

Error::Error(std::string msg) {
    this->type = kError;
    this->msg = msg;
}

std::string Error::Serialize() {
    return std::format(R"({ "type": {}, "msg": {} })", type, msg);
}