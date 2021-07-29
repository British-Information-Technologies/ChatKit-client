#ifndef CPPCHATCLIENT_BASE64_H_
#define CPPCHATCLIENT_BASE64_H_

#include "memory-manager.h"

namespace networking_utility {
secure_string EncodeBase64(secure_string &input_data);

secure_string DecodeBase64(secure_string &encoded_data);
}  // namespace networking_utility

#endif