#include "client-connected.h"

#include <string>
#include <fmt/core.h>
#include <magic_enum.hpp>

using namespace server_stream_in;

ClientConnected::ClientConnected(
    const std::string &id,
    const std::string &username
): id(id), username(username)
{
    this->type = model::Type::ClientConnected;
}

std::string ClientConnected::Serialize() {
    return fmt::format(R"({{ "type": "{}", "id": "{}", "username": "{}" }})", magic_enum::enum_name(type), id, username);
}

model::StreamType ClientConnected::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}