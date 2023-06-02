#include <string>
#include <fmt/core.h>

#include "get-messages.h"

using namespace server_stream_out;

GetMessages::GetMessages() {
    this->type = kGetMessages;
}

std::string GetMessages::Serialize() {
    return fmt::format("{{ \"type\": {} }}", type);
}