#include "public-key.h"

#include <string>
#include <fmt/core.h>
#include <sodium.h>

#include "model/networking/utility/encode.h"

using namespace server_stream_out;

PublicKey::PublicKey(
    const std::string &to,
    const std::string &key
): to(to), key(key)
{
    this->type = kPublicKey;
}

std::string PublicKey::Serialize() {
    return fmt::format("{{ \"type\": {}, \"to\": {}, \"key\": {} }}", type, to, model::Bin2Base64(key));
}

std::string PublicKey::GetKey() {
    return this->key;
}

model::StreamType PublicKey::GetStreamType() {
    return model::StreamType::ServerStreamOut;
}