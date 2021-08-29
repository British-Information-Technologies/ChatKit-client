#ifndef CPPCHATCLIENT_AES_GCM_H_
#define CPPCHATCLIENT_AES_GCM_H_

#include "derived-data.h"
#include "memory-manager.h"

namespace networking_utility {

int aes_gcm_encrypt(std::string &, std::string &, DerivedData *, byte *, int,
                    std::string &, byte *);

int aes_gcm_decrypt(std::string &, int, std::string &, byte *, DerivedData *,
                    byte *, int, std::string &);

}  // namespace networking_utility

#endif