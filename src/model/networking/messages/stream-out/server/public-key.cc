#include "public-key.h"

#include <string>
#include <fmt/core.h>

using namespace server_stream_out;

PublicKey::PublicKey(
    const std::string &to,
    const std::string &key
): to(to), key(key)
{}

std::string PublicKey::Serialize() {
    return fmt::format("{{ \"type\": {}, \"to\": {}, \"key\": {} }}", type, to, key);
}

std::string PublicKey::GetKey() {
    return this->key;
}

model::StreamType PublicKey::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}