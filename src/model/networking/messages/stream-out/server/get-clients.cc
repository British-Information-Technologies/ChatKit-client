#include <string>
#include <fmt/core.h>

#include "get-clients.h"

using namespace server_stream_out;

GetClients::GetClients() {
    this->type = kGetClients;
}

std::string GetClients::Serialize() {
    return fmt::format("{{ \"type\": {} }}", type);
}

model::StreamType GetClients::GetStreamType() {
    return model::StreamType::ServerStreamOut;
}