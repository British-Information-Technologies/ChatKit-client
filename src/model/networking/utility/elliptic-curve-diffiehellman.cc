#include "elliptic-curve-diffiehellman.h"

#include <openssl/ec.h>
#include <openssl/ecdh.h>
#include <openssl/pem.h>

#include <iostream>
#include <nlohmann/json.hpp>

using namespace model_networking_utility;
using json = nlohmann::json;

EVP_PKEY_free_ptr model_networking_utility::GenerateKeyPair() {
  EVP_PKEY_free_ptr pkey(EVP_PKEY_new(), ::EVP_PKEY_free);
  EVP_PKEY_free_ptr params(EVP_PKEY_new(), ::EVP_PKEY_free);

  /* Create the context for parameter generation */
  EVP_PKEY_CTX_free_ptr pctx(EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL),
                             ::EVP_PKEY_CTX_free);

  /* Initialise the parameter generation */
  if (1 != EVP_PKEY_paramgen_init(pctx.get())) abort();
  ;

  /* We're going to use the ANSI X9.62 Prime 256v1 curve */  //
  if (1 != EVP_PKEY_CTX_set_ec_paramgen_curve_nid(pctx.get(), NID_secp256k1))
    abort();
  ;

  /* Create the parameter object params */
  EVP_PKEY *params_ptr = params.get();
  if (!EVP_PKEY_paramgen(pctx.get(), &params_ptr)) abort();
  ;

  /* Create the context for the key generation */
  EVP_PKEY_CTX_free_ptr kctx(EVP_PKEY_CTX_new(params.get(), NULL),
                             ::EVP_PKEY_CTX_free);

  /* Generate the key */
  EVP_PKEY *tmp = pkey.get();
  if (1 != EVP_PKEY_keygen_init(kctx.get())) abort();
  if (1 != EVP_PKEY_keygen(kctx.get(), &tmp)) abort();

  return pkey;
}

std::string model_networking_utility::SerializePublicKey(EVP_PKEY *public_key) {
  BIO_free_ptr bio_public(BIO_new(BIO_s_mem()), ::BIO_free);

  int ret = PEM_write_bio_PUBKEY(bio_public.get(), public_key);
  if (ret != 1) {
    std::cout << "ERROR!" << std::endl;
  }
  BIO_flush(bio_public.get());

  char *public_key_text;
  BIO_get_mem_data(bio_public.get(), &public_key_text);

  json json_public_key = {{"type", "Encrypt"},
                          {"key", std::string(public_key_text)}};

  return json_public_key.dump();
}

EVP_PKEY_free_ptr model_networking_utility::DeserializePublicKey(
    const char *buffer) {
  json json_object = json::parse(buffer);
  std::string public_key = json_object["key"];

  BIO_free_ptr mem(BIO_new_mem_buf(public_key.c_str(), -1), ::BIO_free);

  EVP_PKEY_free_ptr evp_public_key(
      PEM_read_bio_PUBKEY(mem.get(), NULL, NULL, 0), ::EVP_PKEY_free);

  return evp_public_key;
}

/* Extract a public key from a provided key pair */
EVP_PKEY_free_ptr model_networking_utility::ExtractPublicKey(
    EVP_PKEY *private_key) {
  EC_KEY_free_ptr ec_key(EVP_PKEY_get1_EC_KEY(private_key), ::EC_KEY_free);
  const EC_POINT *ec_point = EC_KEY_get0_public_key(ec_key.get());

  EVP_PKEY_free_ptr public_key(EVP_PKEY_new(), ::EVP_PKEY_free);
  EC_KEY_free_ptr public_ec_key(EC_KEY_new_by_curve_name(NID_secp256k1),
                                ::EC_KEY_free);

  EC_KEY_set_public_key(public_ec_key.get(), ec_point);
  EVP_PKEY_set1_EC_KEY(public_key.get(), public_ec_key.get());

  return public_key;
}

/*Creates a 512 bit value from a peers public key and your own private
  key.

  Never use a derived secret directly. Typically it is passed through
  some hash function to produce a key. */
DerivedData *model_networking_utility::DeriveSharedSecret(
    EVP_PKEY *public_key, EVP_PKEY *private_key) {
  DerivedData *derived_key = (DerivedData *)malloc(sizeof(DerivedData));

  /* Create the context for the shared secret derivation */
  EVP_PKEY_CTX_free_ptr ctx(EVP_PKEY_CTX_new(private_key, NULL),
                            ::EVP_PKEY_CTX_free);

  /* Initialise */
  if (1 != EVP_PKEY_derive_init(ctx.get())) abort();

  /* Provide the peer public key */
  if (1 != EVP_PKEY_derive_set_peer(ctx.get(), public_key)) abort();

  /* Determine buffer length for shared secret */
  if (1 != EVP_PKEY_derive(ctx.get(), NULL, &derived_key->length)) {
    abort();
  }

  if (NULL ==
      (derived_key->secret = (unsigned char *)malloc(derived_key->length))) {
    abort();
  }

  /* Derive the shared secret */
  if (1 !=
      (EVP_PKEY_derive(ctx.get(), derived_key->secret, &derived_key->length))) {
    abort();
  }

  return derived_key;
}