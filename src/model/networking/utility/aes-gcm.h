#ifndef MODEL_NETWORKING_UTILITY_AES_GCM_H_
#define MODEL_NETWORKING_UTILITY_AES_GCM_H_

#include "derived-data.h"
#include "memory-manager.h"

namespace model_networking_utility {

int AesGcmEncrypt(std::string &, std::string &, DerivedData *, byte *, int,
                  std::string &, byte *);

int AesGcmDecrypt(std::string &, int, std::string &, byte *, DerivedData *,
                  byte *, int, std::string &);

}  // namespace model_networking_utility

#endif