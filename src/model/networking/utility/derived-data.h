#ifndef MODEL_NETWORKING_UTILITY_DERIVED_DATA_H_
#define MODEL_NETWORKING_UTILITY_DERIVED_DATA_H_

#include <cstddef>

namespace model_networking_utility {

struct DerivedData {
  unsigned char *secret;
  size_t length;
};

}  // namespace model_networking_utility

#endif