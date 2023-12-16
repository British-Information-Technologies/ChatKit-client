#include "public-key.h"

#include <fmt/core.h>
#include <magic_enum.hpp>
#include <sodium.h>
#include <string>

#include "model/networking/utility/decode.h"

using namespace server_stream_in;

PublicKey::PublicKey(
    const std::string& from,
    const std::string& key) : from(from), key(key) {
    this->type = model::Type::PublicKey;
}

std::string PublicKey::Serialize() {
    return fmt::format(R"({{ "type": "{}", "from": "{}", "key": "{}" }})", magic_enum::enum_name(type), from, key);
}

std::string PublicKey::GetFrom() {
    return this->from;
}

unsigned char* PublicKey::GetKey() {
    auto [key, _] = model::Base642Bin(this->key);
    return key;
}

model::StreamType PublicKey::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}