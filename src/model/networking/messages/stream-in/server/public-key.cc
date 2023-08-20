#include "public-key.h"

#include <string>
#include <fmt/core.h>
#include <sodium.h>
#include <magic_enum.hpp>

#include "model/networking/utility/encode.h"

using namespace server_stream_in;

PublicKey::PublicKey(const std::string &key): key(key) {
    this->type = model::Type::PublicKey;
}

std::string PublicKey::Serialize() {
    return fmt::format("{{ \"type\": {}, \"key\": {} }}", magic_enum::enum_name(type), model::Bin2Base64(key));
}

std::string PublicKey::GetKey() {
    return this->key;
}

model::StreamType PublicKey::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}