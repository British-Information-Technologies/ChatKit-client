#include <fmt/core.h>
#include <magic_enum.hpp>
#include <string>

#include "get-clients.h"

using namespace server_stream_out;

GetClients::GetClients() {
    this->type = model::Type::GetClients;
}

std::string GetClients::Serialize() {
    return fmt::format(R"({{ "type": "{}" }})", magic_enum::enum_name(type));
}

model::StreamType GetClients::GetStreamType() {
    return model::StreamType::ServerStreamOut;
}