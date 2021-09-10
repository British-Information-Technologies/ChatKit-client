#ifndef MODEL_NETWORKING_UTILITY_ELLIPTIC_CURVE_DIFFIEHELLMAN_H_
#define MODEL_NETWORKING_UTILITY_ELLIPTIC_CURVE_DIFFIEHELLMAN_H_

#include <openssl/evp.h>

#include <memory>

#include "crypto-types.h"
#include "derived-data.h"

namespace model_networking_utility {

EVP_PKEY_free_ptr GenerateKeyPair();
EVP_PKEY_free_ptr ExtractPublicKey(EVP_PKEY *);
std::string SerializePublicKey(EVP_PKEY *);
EVP_PKEY_free_ptr DeserializePublicKey(const char *);
DerivedData *DeriveSharedSecret(EVP_PKEY *, EVP_PKEY *);

}  // namespace model_networking_utility

#endif