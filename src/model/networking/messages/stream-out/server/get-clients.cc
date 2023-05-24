#include <string>
#include <format>

#include "get-clients.h"

using namespace server_stream_out;

GetClients::GetClients() {
    this->type = kGetClients;
}

std::string GetClients::Serialize() {
    return std::format(R"({ "type": {} })", type);
}