#include <fmt/core.h>
#include <magic_enum.hpp>
#include <string>

#include "got-info.h"

using namespace network_stream_in;

GotInfo::GotInfo(
    const std::string& server_name,
    const std::string& server_owner) : server_name(server_name), server_owner(server_owner) {
    this->type = model::Type::GotInfo;
}

std::string GotInfo::GetServerAlias() {
    return server_name;
}

std::string GotInfo::GetServerOwner() {
    return server_owner;
}

std::string GotInfo::Serialize() {
    return fmt::format(R"({{ "type": "{}", "server_name": "{}", "server_owner": "{}" }})", magic_enum::enum_name(type), server_name, server_owner);
}

model::StreamType GotInfo::GetStreamType() {
    return model::StreamType::NetworkStreamIn;
}