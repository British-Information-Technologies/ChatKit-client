#include <fmt/core.h>
#include <magic_enum.hpp>
#include <string>

#include "connect.h"

using namespace network_stream_out;

Connect::Connect(
    const std::string& uuid,
    const std::string& username,
    const std::string& address) : uuid(uuid), username(username), address(address) {
    this->type = model::Type::Connect;
}

std::string Connect::Serialize() {
    return fmt::format(R"({{ "type": "{}", "uuid": "{}", "username": "{}", "address": "{}" }})", magic_enum::enum_name(type), uuid, username, address);
}

model::StreamType Connect::GetStreamType() {
    return model::StreamType::NetworkStreamOut;
}