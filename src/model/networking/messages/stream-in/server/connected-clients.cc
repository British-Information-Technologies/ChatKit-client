#include "connected-clients.h"

#include <nlohmann/json.hpp>
#include <string>
#include <fmt/core.h>
#include <magic_enum.hpp>

using json = nlohmann::json;

using namespace server_stream_in;

ConnectedClients::ConnectedClients(const json &clients): clients(clients) {
    this->type = model::Type::ConnectedClients;
}

std::string ConnectedClients::Serialize() {
    return fmt::format(R"({{ "type": "{}", "clients": "{}" }})", magic_enum::enum_name(type), clients.dump());
}

model::StreamType ConnectedClients::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}