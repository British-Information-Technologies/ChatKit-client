#ifndef MODEL_NETWORKING_UTILITY_DECODE_H_
#define MODEL_NETWORKING_UTILITY_DECODE_H_

#include <string>
#include <tuple>

namespace model {
    std::tuple<unsigned char*, size_t> Base642Bin(const std::string &encoded_data);
} // namespace model

#endif