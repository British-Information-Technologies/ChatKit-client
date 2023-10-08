#ifndef MODEL_NETWORKING_UTILITY_ENCODE_H_
#define MODEL_NETWORKING_UTILITY_ENCODE_H_

#include <string>

namespace model {
    std::string Bin2Base64(const unsigned char *data, unsigned long long data_len);
} // namespace model

#endif