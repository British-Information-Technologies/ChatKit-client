#include "public-key.h"

#include <string>
#include <fmt/core.h>
#include <sodium.h>
#include <magic_enum.hpp>

#include "model/networking/utility/encode.h"

using namespace server_stream_out;

PublicKey::PublicKey(
    const std::string &to,
    const std::string &key
): to(to), key(key)
{
    this->type = model::Type::PublicKey;
}

std::string PublicKey::Serialize() {
    return fmt::format(R"({{ "type": "{}", "to": "{}", "key": "{}" }})", magic_enum::enum_name(type), to, model::Bin2Base64(key));
}

std::string PublicKey::GetKey() {
    return this->key;
}

model::StreamType PublicKey::GetStreamType() {
    return model::StreamType::ServerStreamOut;
}