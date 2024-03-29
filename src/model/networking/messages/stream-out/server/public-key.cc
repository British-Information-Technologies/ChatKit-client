#include "public-key.h"

#include <fmt/core.h>
#include <magic_enum.hpp>
#include <sodium.h>
#include <string>

#include "model/networking/utility/decode.h"

using namespace server_stream_out;

PublicKey::PublicKey(
    const std::string& to,
    const std::string& key) : to(to), key(key) {
    this->type = model::Type::PublicKey;
}

std::string PublicKey::Serialize() {
    return fmt::format(R"({{ "type": "{}", "to": "{}", "key": "{}" }})", magic_enum::enum_name(type), to, key);
}

unsigned char* PublicKey::GetKey() {
    auto [key, _] = model::Base642Bin(this->key);
    return key;
}

model::StreamType PublicKey::GetStreamType() {
    return model::StreamType::ServerStreamOut;
}