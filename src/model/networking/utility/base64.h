#ifndef MODEL_NETWORKING_UTILITY_BASE64_H_
#define MODEL_NETWORKING_UTILITY_BASE64_H_

#include "memory-manager.h"

namespace model_networking_utility {
std::string EncodeBase64(std::string &input_data);

std::string DecodeBase64(std::string &encoded_data);
}  // namespace model_networking_utility

#endif