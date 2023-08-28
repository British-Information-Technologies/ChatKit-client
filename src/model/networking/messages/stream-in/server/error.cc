#include "error.h"

#include <string>
#include <fmt/core.h>
#include <magic_enum.hpp>

using namespace server_stream_in;

Error::Error(const std::string &msg): msg(msg) {
    this->type = model::Type::Error;
}

std::string Error::Serialize() {
    return fmt::format(R"({{ "type": "{}", "msg": "{}" }})", magic_enum::enum_name(type), msg);
}

model::StreamType Error::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}