#include "client-removed.h"

#include <string>
#include <fmt/core.h>
#include <magic_enum.hpp>

using namespace server_stream_in;

ClientRemoved::ClientRemoved(const std::string &id): id(id) {
    this->type = model::Type::ClientRemoved;
}

std::string ClientRemoved::Serialize() {
    return fmt::format(R"({{ "type": "{}", "id": "{}" }})", magic_enum::enum_name(type), id);
}

model::StreamType ClientRemoved::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}