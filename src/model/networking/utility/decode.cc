#include <iostream>
#include <memory>
#include <string>
#include <tuple>

#include "decode.h"

#include "model/networking/utility/variants.h"

std::tuple<unsigned char*, size_t> model::Base642Bin(const std::string& encoded_data) {
    size_t encoded_data_len = encoded_data.length();

    size_t data_len = (encoded_data_len * 3) / 4; // - n (n is padding char =, 0 <= n < 3)

    unsigned char* data_ptr = (unsigned char*)malloc(sizeof(unsigned char) * data_len);

    sodium_base642bin(
        data_ptr,
        data_len,
        encoded_data.c_str(),
        encoded_data_len,
        NULL,
        &data_len,
        NULL,
        base64_VARIANT_NO_PADDING);

    return std::tuple(data_ptr, data_len);
}