#include "connected-clients.h"

#include <nlohmann/json.hpp>
#include <string>
#include <format>

using json = nlohmann::json;

using namespace server_stream_in;

ConnectedClients::ConnectedClients(json clients) {
    this->type = kConnectedClients;
    this->clients = clients;
}

std::string ConnectedClients::Serialize() {
    return std::format(R"({ "type": {}, "clients": {} })", type, clients.dump());
}