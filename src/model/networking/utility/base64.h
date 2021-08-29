#ifndef CPPCHATCLIENT_BASE64_H_
#define CPPCHATCLIENT_BASE64_H_

#include "memory-manager.h"

namespace networking_utility {
std::string EncodeBase64(std::string &input_data);

std::string DecodeBase64(std::string &encoded_data);
}  // namespace networking_utility

#endif