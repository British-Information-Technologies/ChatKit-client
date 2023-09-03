#include <string>
#include <memory>

#include "decode.h"

#include "model/networking/utility/variants.h"

unsigned char* model::Base642Bin(const std::string &encoded_data) {
    size_t encoded_data_len = encoded_data.length();

    size_t data_len = encoded_data_len / 4 * 3; // ( - padding) base64 encodes 3 bytes as 4 characters (= char is padding, could make better by removing padding)
    unsigned char *data_ptr = (unsigned char*) malloc(sizeof(unsigned char) * data_len);

    sodium_base642bin(
        data_ptr,
        data_len,
        encoded_data.c_str(),
        encoded_data_len + 1,
        NULL,
        &data_len,
        NULL,
        base64_VARIANT
    );

    return data_ptr;
}