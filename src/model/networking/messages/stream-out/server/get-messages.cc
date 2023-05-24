#include <string>
#include <format>

#include "get-messages.h"

using namespace server_stream_out;

GetMessages::GetMessages() {
    this->type = kGetMessages;
}

std::string GetMessages::Serialize() {
    return std::format(R"({ "type": {} })", type);
}