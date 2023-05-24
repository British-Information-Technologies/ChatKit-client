#include <string>
#include <format>

#include "connect.h"

using namespace network_stream_out;

Connect::Connect(std::string uuid, std::string username, std::string address) {
    this->type = kConnect;
    this->uuid = uuid;
    this->username = username;
    this->address = address;
}

std::string Connect::Serialize() {
    return std::format(R"({ "type": {}, "uuid": {}, "username": {}, "address": {} })", type, uuid, username, address);
}