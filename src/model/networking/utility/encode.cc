#include <string>
#include <cstring>

#include "encode.h"

#include "model/networking/utility/variants.h"

std::string model::Bin2Base64(const unsigned char *data) {
    unsigned long long data_len = std::strlen((char*) data) + 1;

    unsigned long long encoded_data_len = sodium_base64_ENCODED_LEN(data_len, base64_VARIANT);
    char encoded_data[encoded_data_len];
    sodium_bin2base64(
        encoded_data,
        encoded_data_len,
        data,
        data_len,
        base64_VARIANT
    );

    return encoded_data;
}