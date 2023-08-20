#include <string>

#include "decode.h"

#include "model/networking/utility/variants.h"

std::string model::Base642Bin(const std::string &encoded_data) {
    const char* encoded_data_ptr = reinterpret_cast<const char*>(encoded_data.c_str());

    size_t data_len = encoded_data.length() / 4 * 3; // base64 encodes 3 bytes as 4 characters
    unsigned char data_ptr[data_len];
    sodium_base642bin(
        data_ptr,
        data_len,
        encoded_data_ptr,
        sizeof encoded_data_ptr,
        NULL,
        &data_len,
        NULL,
        base64_VARIANT
    );
    
    return std::string(reinterpret_cast<char const*>(data_ptr), data_len);
}