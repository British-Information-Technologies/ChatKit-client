#include "public-key.h"

#include <string>
#include <fmt/core.h>

using namespace server_stream_in;

PublicKey::PublicKey(std::string key) {
    this->type = kPublicKey;
    this->key = key;
}

std::string PublicKey::Serialize() {
    return fmt::format("{{ \"type\": {}, \"key\": {} }}", type, key);
}

std::string PublicKey::GetKey() {
    return this->key;
}
