#include "public-key.h"

#include <string>
#include <fmt/core.h>
#include <sodium.h>
#include <magic_enum.hpp>

#include "model/networking/utility/encode.h"

using namespace server_stream_in;

PublicKey::PublicKey(
    const std::string &from,
    const std::string &key
): from(from), key(key)
{
    this->type = model::Type::PublicKey;
}

std::string PublicKey::Serialize() {
    return fmt::format(R"({{ "type": "{}", "from": "{}", "key": "{}" }})", magic_enum::enum_name(type), from, model::Bin2Base64(key));
}

std::string PublicKey::GetFrom() {
    return this->from;
}

std::string PublicKey::GetKey() {
    return this->key;
}

model::StreamType PublicKey::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}