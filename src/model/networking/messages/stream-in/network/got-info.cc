#include <string>
#include <format>

#include "got-info.h"

using namespace network_stream_in;

GotInfo::GotInfo(std::string server_name, std::string server_owner) {
    this->type = kGotInfo;
    this->server_name = server_name;
    this->server_owner = server_owner;
}

std::string GotInfo::Serialize() {
    return std::format(R"({ "type": {}, "server_name": {}, "server_owner": {} })", type, server_name, server_owner);
}