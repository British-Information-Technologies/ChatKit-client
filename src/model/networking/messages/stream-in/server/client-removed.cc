#include "client-removed.h"

#include <string>
#include <fmt/core.h>

using namespace server_stream_in;

ClientRemoved::ClientRemoved(std::string id) {
    this->type = kClientRemoved;
    this->type = id;
}

std::string ClientRemoved::Serialize() {
    return fmt::format("{{ \"type\": {}, \"id\": {} }}", type, id);
}