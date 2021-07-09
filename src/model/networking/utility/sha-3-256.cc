#include "sha-3-256.h"

#include <openssl/evp.h>

#include <cstring>
#include <iostream>
#include <memory>

using namespace networking_utility;

using EVP_MD_CTX_free_ptr =
    std::unique_ptr<EVP_MD_CTX, decltype(&::EVP_MD_CTX_free)>;

void networking_utility::HashData(DerivedData *data) {
  const EVP_MD *hashing_algorithm = EVP_sha3_256();
  EVP_MD_CTX_free_ptr mdctx(EVP_MD_CTX_create(), ::EVP_MD_CTX_free);

  // initialize digest engine
  if (EVP_DigestInit_ex(mdctx.get(), hashing_algorithm, NULL) != 1) {
    abort();
  }

  // provide data to digest engine
  if (EVP_DigestUpdate(mdctx.get(), data->secret, data->length) != 1) {
    abort();
  }

  unsigned int digest_length = EVP_MD_size(hashing_algorithm);
  unsigned char *digest = (unsigned char *)malloc(digest_length);
  if (digest == NULL) {
    abort();
  }

  // produce digest
  if (EVP_DigestFinal_ex(mdctx.get(), digest, &digest_length) != 1) {
    free(digest);
    abort();
  }

  data->length = digest_length;
  free(data->secret);
  if (NULL == (data->secret = (unsigned char *)malloc(data->length))) {
    free(digest);
    abort();
  }

  strcpy((char *)data->secret, (const char *)digest);
  free(digest);
}