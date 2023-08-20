#include <string>

#include "encode.h"

#include "model/networking/utility/variants.h"

std::string model::Bin2Base64(const std::string &data) {
    const unsigned char* data_ptr = reinterpret_cast<const unsigned char*>(data.c_str());
    unsigned long long data_len = sizeof data_ptr;

    char encoded_data[sodium_base64_ENCODED_LEN(data_len, base64_VARIANT)];
    sodium_bin2base64(
        encoded_data,
        sizeof encoded_data,
        data_ptr,
        data_len,
        base64_VARIANT
    );

    return encoded_data;
}