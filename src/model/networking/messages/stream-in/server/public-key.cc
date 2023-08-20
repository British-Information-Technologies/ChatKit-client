#include "public-key.h"

#include <string>
#include <fmt/core.h>
#include <sodium.h>

#include "model/networking/utility/encode.h"

using namespace server_stream_in;

PublicKey::PublicKey(std::string key) {
    this->type = kPublicKey;
    this->key = key;
}

std::string PublicKey::Serialize() {
    return fmt::format("{{ \"type\": {}, \"key\": {} }}", type, model::Bin2Base64(key));
}

std::string PublicKey::GetKey() {
    return this->key;
}

model::StreamType PublicKey::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}