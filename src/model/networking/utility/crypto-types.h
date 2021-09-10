
#ifndef MODEL_NETWORKING_UTILITY_CRYPTO_TYPES_H_
#define MODEL_NETWORKING_UTILITY_CRYPTO_TYPES_H_

#include <openssl/ec.h>
#include <openssl/evp.h>

#include <memory>

using EVP_CIPHER_CTX_free_ptr =
    std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;

using EVP_PKEY_CTX_free_ptr =
    std::unique_ptr<EVP_PKEY_CTX, decltype(&::EVP_PKEY_CTX_free)>;

using EC_KEY_free_ptr = std::unique_ptr<EC_KEY, decltype(&::EC_KEY_free)>;

using BIO_free_ptr = std::unique_ptr<BIO, decltype(&::BIO_free)>;

using EVP_PKEY_free_ptr = std::unique_ptr<EVP_PKEY, decltype(&::EVP_PKEY_free)>;

using EVP_MD_CTX_free_ptr =
    std::unique_ptr<EVP_MD_CTX, decltype(&::EVP_MD_CTX_free)>;

#endif