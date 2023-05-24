#include "client-connected.h"

#include <string>
#include <format>

using namespace server_stream_in;

ClientConnected::ClientConnected(std::string id, std::string username) {
    this->type = kClientConnected;
    this->id = id;
    this->username = username;
}

std::string ClientConnected::Serialize() {
    return std::format(R"({ "type": {}, "id": {}, "username": {} })", type, id, username);
}