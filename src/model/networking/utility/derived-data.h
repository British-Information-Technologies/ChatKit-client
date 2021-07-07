#ifndef CPPCHATCLIENT_DERIVED_DATA_H_
#define CPPCHATCLIENT_DERIVED_DATA_H_

#include <cstddef>

namespace networking_utility {

struct DerivedData {
  unsigned char *secret;
  size_t length;
};

}  // namespace networking_utility

#endif