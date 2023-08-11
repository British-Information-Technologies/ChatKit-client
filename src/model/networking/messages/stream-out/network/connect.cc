#include <string>
#include <fmt/core.h>

#include "connect.h"

using namespace network_stream_out;

Connect::Connect(std::string uuid, std::string username, std::string address) {
    this->type = kConnect;
    this->uuid = uuid;
    this->username = username;
    this->address = address;
}

std::string Connect::Serialize() {
    return fmt::format("{{ \"type\": {}, \"uuid\": {}, \"username\": {}, \"address\": {} }}", type, uuid, username, address);
}
            
model::StreamType Connect::GetStreamType() {
    return model::StreamType::NetworkStreamOut;
}