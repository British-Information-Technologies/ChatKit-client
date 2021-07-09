#ifndef CPPCHATCLIENT_AES_GCM_H_
#define CPPCHATCLIENT_AES_GCM_H_

#include "derived-data.h"
#include "memory-manager.h"

namespace networking_utility {

int aes_gcm_encrypt(secure_string &, secure_string &, DerivedData *, byte *,
                    int, secure_string &, byte *);

int aes_gcm_decrypt(secure_string &, int, secure_string &, byte *,
                    DerivedData *, byte *, int, secure_string &);

}  // namespace networking_utility

#endif