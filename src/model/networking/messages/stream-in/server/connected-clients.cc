#include "connected-clients.h"

#include <nlohmann/json.hpp>
#include <string>
#include <fmt/core.h>

using json = nlohmann::json;

using namespace server_stream_in;

ConnectedClients::ConnectedClients(json clients) {
    this->type = kConnectedClients;
    this->clients = clients;
}

std::string ConnectedClients::Serialize() {
    return fmt::format("{{ \"type\": {}, \"clients\": {} }}", type, clients.dump());
}

model::StreamType ConnectedClients::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}