#ifndef CPPCHATCLIENT_ELLIPTIC_CURVE_DIFFIEHELLMAN_H_
#define CPPCHATCLIENT_ELLIPTIC_CURVE_DIFFIEHELLMAN_H_

/* Never use a derived secret (final result) directly. Typically it is passed
 * through some hash function to produce a key.

  Must remember to free the keys when done!
  EVP_PKEY_free(peerkey);
  EVP_PKEY_free(pkey); */

#include <openssl/ec.h>
#include <openssl/ecdh.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>

namespace key_agreement {

template <typename T>
struct zallocator {
 public:
  typedef T value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  pointer address(reference v) const { return &v; }
  const_pointer address(const_reference v) const { return &v; }

  pointer allocate(size_type n, const void *hint = 0) {
    if (n > std::numeric_limits<size_type>::max() / sizeof(T))
      throw std::bad_alloc();
    return static_cast<pointer>(::operator new(n * sizeof(value_type)));
  }

  void deallocate(pointer p, size_type n) {
    OPENSSL_cleanse(p, n * sizeof(T));
    ::operator delete(p);
  }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(T);
  }

  template <typename U>
  struct rebind {
    typedef zallocator<U> other;
  };

  template <typename U, typename... Args>
  void construct(U *ptr, Args &&...args) {
    ::new (static_cast<void *>(ptr)) U(std::forward<Args>(args)...);
  }

  template <typename U>
  void destroy(U *ptr) {
    ptr->~U();
  }
};

typedef std::basic_string<char, std::char_traits<char>, zallocator<char> >
    secure_string;

using EVP_CIPHER_CTX_free_ptr =
    std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;

using EVP_PKEY_CTX_free_ptr =
    std::unique_ptr<EVP_PKEY_CTX, decltype(&::EVP_PKEY_CTX_free)>;

using EVP_PKEY_free_ptr = std::unique_ptr<EVP_PKEY, decltype(&::EVP_PKEY_free)>;

using EC_KEY_free_ptr = std::unique_ptr<EC_KEY, decltype(&::EC_KEY_free)>;

struct DerivedKey {
  unsigned char *secret;
  size_t length;
};

typedef struct DerivedKey derivedKey;

EVP_PKEY_free_ptr GenerateKeyPair();
EVP_PKEY_free_ptr ExtractPublicKey(EVP_PKEY *private_key);
DerivedKey *DeriveSharedSecret(EVP_PKEY *public_key, EVP_PKEY *private_key);
void handleErrors(void);

EVP_PKEY_free_ptr GenerateKeyPair() {
  // EVP_PKEY_CTX *pctx, *kctx;
  // EVP_PKEY_CTX *kctx;
  // EVP_PKEY *pkey = NULL,
  EVP_PKEY_free_ptr pkey(EVP_PKEY_new(), ::EVP_PKEY_free);
  EVP_PKEY_free_ptr params(EVP_PKEY_new(), ::EVP_PKEY_free);

  /* Create the context for parameter generation */
  // if (NULL == (pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL)))
  // handleErrors();
  EVP_PKEY_CTX_free_ptr pctx(EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL),
                             ::EVP_PKEY_CTX_free);

  /* Initialise the parameter generation */
  if (1 != EVP_PKEY_paramgen_init(pctx.get())) handleErrors();

  /* We're going to use the ANSI X9.62 Prime 256v1 curve */  //
  if (1 != EVP_PKEY_CTX_set_ec_paramgen_curve_nid(pctx.get(), NID_secp521r1))
    handleErrors();

  /* Create the parameter object params */
  EVP_PKEY *params_ptr = params.get();
  if (!EVP_PKEY_paramgen(pctx.get(), &params_ptr)) handleErrors();

  /* Create the context for the key generation */
  // if (NULL == (kctx = EVP_PKEY_CTX_new(params, NULL))) handleErrors();
  EVP_PKEY_CTX_free_ptr kctx(EVP_PKEY_CTX_new(params.get(), NULL),
                             ::EVP_PKEY_CTX_free);

  /* Generate the key */
  EVP_PKEY *tmp = pkey.get();
  if (1 != EVP_PKEY_keygen_init(kctx.get())) handleErrors();
  if (1 != EVP_PKEY_keygen(kctx.get(), &tmp)) handleErrors();

  return pkey;
}

/* Get the peer's public key, and provide the peer with our public key -
 * how this is done will be specific to your circumstances */
// TODO!
EVP_PKEY_free_ptr ExtractPublicKey(EVP_PKEY *private_key) {
  // EC_KEY *ec_key = EVP_PKEY_get1_EC_KEY(private_key);
  EC_KEY_free_ptr ec_key(EVP_PKEY_get1_EC_KEY(private_key), ::EC_KEY_free);

  const EC_POINT *ec_point = EC_KEY_get0_public_key(ec_key.get());

  // EVP_PKEY *public_key = EVP_PKEY_new();
  EVP_PKEY_free_ptr public_key(EVP_PKEY_new(), ::EVP_PKEY_free);

  // EC_KEY *public_ec_key = EC_KEY_new_by_curve_name(NID_secp521r1);
  EC_KEY_free_ptr public_ec_key(EC_KEY_new_by_curve_name(NID_secp521r1),
                                ::EC_KEY_free);

  EC_KEY_set_public_key(public_ec_key.get(), ec_point);
  EVP_PKEY_set1_EC_KEY(public_key.get(), public_ec_key.get());

  return public_key;
}

DerivedKey *DeriveSharedSecret(EVP_PKEY *public_key, EVP_PKEY *private_key) {
  DerivedKey *derived_key = (DerivedKey *)malloc(sizeof(DerivedKey));
  // EVP_PKEY_CTX *ctx;

  /* Create the context for the shared secret derivation */
  // if (NULL == (ctx = EVP_PKEY_CTX_new(private_key, NULL))) handleErrors();
  EVP_PKEY_CTX_free_ptr ctx(EVP_PKEY_CTX_new(private_key, NULL),
                            ::EVP_PKEY_CTX_free);

  /* Initialise */
  if (1 != EVP_PKEY_derive_init(ctx.get())) handleErrors();

  /* Provide the peer public key */
  if (1 != EVP_PKEY_derive_set_peer(ctx.get(), public_key)) handleErrors();

  /* Determine buffer length for shared secret */
  if (1 != EVP_PKEY_derive(ctx.get(), NULL, &derived_key->length)) {
    handleErrors();
  }

  if (NULL ==
      (derived_key->secret = (unsigned char *)malloc(derived_key->length))) {
    handleErrors();
  }

  /* Derive the shared secret */
  if (1 !=
      (EVP_PKEY_derive(ctx.get(), derived_key->secret, &derived_key->length))) {
    handleErrors();
  }

  // EVP_PKEY_CTX_free(ctx);

  return derived_key;
}

/*For testing purposes this is fine but really should'nt
  be like this as an end result! */
void handleErrors(void) {
  std::cout << "Failed" << std::endl;
  abort();
}
}  // namespace key_agreement

#endif