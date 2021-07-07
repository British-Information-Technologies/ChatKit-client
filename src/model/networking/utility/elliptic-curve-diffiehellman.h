#ifndef CPPCHATCLIENT_ELLIPTIC_CURVE_DIFFIEHELLMAN_H_
#define CPPCHATCLIENT_ELLIPTIC_CURVE_DIFFIEHELLMAN_H_

#include <openssl/evp.h>

#include <memory>

#include "derived-data.h"

namespace networking_utility {

using EVP_PKEY_free_ptr = std::unique_ptr<EVP_PKEY, decltype(&::EVP_PKEY_free)>;

EVP_PKEY_free_ptr GenerateKeyPair();
EVP_PKEY_free_ptr ExtractPublicKey(EVP_PKEY *private_key);
DerivedData *DeriveSharedSecret(EVP_PKEY *public_key, EVP_PKEY *private_key);

}  // namespace networking_utility

#endif