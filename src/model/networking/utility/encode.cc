#include <cstring>
#include <string>

#include "encode.h"

#include "model/networking/utility/variants.h"

std::string model::Bin2Base64(const unsigned char* data, unsigned long long data_len) {
    unsigned long long encoded_data_len = sodium_base64_ENCODED_LEN(data_len, base64_VARIANT_NO_PADDING);
    char encoded_data[encoded_data_len];

    sodium_bin2base64(
        encoded_data,
        encoded_data_len,
        data,
        data_len,
        base64_VARIANT_NO_PADDING);

    return encoded_data;
}