#include "public-key.h"

#include <string>
#include <fmt/core.h>
#include <sodium.h>

#include "model/networking/utility/variants.h"

using namespace server_stream_in;

PublicKey::PublicKey(std::string key) {
    this->type = kPublicKey;
    this->key = key;
}

std::string PublicKey::Serialize() {
    const unsigned char* key_ptr = reinterpret_cast<const unsigned char*>(key.c_str());
    unsigned long long key_len = sizeof key_ptr;

    unsigned long long encoded_key_len = sodium_base64_ENCODED_LEN(key_len, base64_VARIANT);
    char encoded_key[encoded_key_len];
    
    sodium_bin2base64(
        encoded_key,
        encoded_key_len,
        key_ptr,
        key_len,
        base64_VARIANT
    );
    
    return fmt::format("{{ \"type\": {}, \"key\": {} }}", type, std::string(encoded_key, encoded_key_len));
}

std::string PublicKey::GetKey() {
    return this->key;
}

model::StreamType PublicKey::GetStreamType() {
    return model::StreamType::ServerStreamIn;
}