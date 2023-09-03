#ifndef MODEL_NETWORKING_UTILITY_DECODE_H_
#define MODEL_NETWORKING_UTILITY_DECODE_H_

#include <string>

namespace model {
    unsigned char* Base642Bin(const std::string &encoded_data);
} // namespace model

#endif