#ifndef CPPCHATCLIENT_ELLIPTIC_CURVE_DIFFIEHELLMAN_H_
#define CPPCHATCLIENT_ELLIPTIC_CURVE_DIFFIEHELLMAN_H_

#include <openssl/evp.h>

#include <memory>

#include "crypto-types.h"
#include "derived-data.h"

namespace networking_utility {

EVP_PKEY_free_ptr GenerateKeyPair();
EVP_PKEY_free_ptr ExtractPublicKey(EVP_PKEY *);
std::string SerializePublicKey(EVP_PKEY *);
EVP_PKEY_free_ptr DeserializePublicKey(const char *);
DerivedData *DeriveSharedSecret(EVP_PKEY *, EVP_PKEY *);

}  // namespace networking_utility

#endif