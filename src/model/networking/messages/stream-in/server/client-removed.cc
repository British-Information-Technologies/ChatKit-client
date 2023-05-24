#include "client-removed.h"

#include <string>
#include <format>

using namespace server_stream_in;

ClientRemoved::ClientRemoved(std::string id) {
    this->type = kClientRemoved;
    this->type = id;
}

std::string ClientRemoved::Serialize() {
    return std::format(R"({ "type": {}, "id": {} })", type, id);
}