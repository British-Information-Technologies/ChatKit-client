#include "aes-gcm.h"

#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <string.h>

#include "base64.h"

using namespace networking_utility;

using EVP_CIPHER_CTX_free_ptr =
    std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;

int networking_utility::aes_gcm_encrypt(secure_string &plaintext,
                                        secure_string &aad, DerivedData *key,
                                        byte *iv, int iv_len,
                                        secure_string &ciphertext, byte *tag) {
  int len;
  int ciphertext_len;

  /* Create and initialise the context */
  EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);

  /* Initialise the encryption operation. */
  if (1 != EVP_EncryptInit_ex(ctx.get(), EVP_aes_256_gcm(), NULL, NULL, NULL))
    abort();

  ciphertext.resize(plaintext.size());

  /*
   * Set IV length if default 12 bytes (96 bits) is not appropriate
   */
  if (1 != EVP_CIPHER_CTX_ctrl(ctx.get(), EVP_CTRL_GCM_SET_IVLEN, iv_len, NULL))
    abort();

  /* Initialise key and IV */
  if (1 != EVP_EncryptInit_ex(ctx.get(), NULL, NULL, key->secret, iv)) abort();

  /*
   * Provide any AAD data. This can be called zero or more times as
   * required
   */
  if (1 != EVP_EncryptUpdate(ctx.get(), NULL, &len, (byte *)&aad[0],
                             (int)aad.size()))
    abort();

  /*
   * Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if (1 != EVP_EncryptUpdate(ctx.get(), (byte *)&ciphertext[0], &len,
                             (const byte *)&plaintext[0],
                             (int)plaintext.size()))
    abort();
  ciphertext_len = len;

  /*
   * Finalise the encryption. Normally ciphertext bytes may be written at
   * this stage, but this does not occur in GCM mode
   */
  if (1 != EVP_EncryptFinal_ex(ctx.get(), (byte *)&ciphertext[0] + len, &len))
    abort();
  ciphertext_len += len;

  /* Get the tag */
  if (1 != EVP_CIPHER_CTX_ctrl(ctx.get(), EVP_CTRL_GCM_GET_TAG, 16, tag))
    abort();

  /* BASE 64 encode the ciphertext */
  ciphertext.assign((std::string)EncodeBase64(ciphertext));
  ciphertext_len = ciphertext.length();

  return ciphertext_len;
}

int networking_utility::aes_gcm_decrypt(secure_string &ciphertext,
                                        int ciphertext_len, secure_string &aad,
                                        byte *tag, DerivedData *key, byte *iv,
                                        int iv_len, secure_string &plaintext) {
  int len;
  int plaintext_len;
  int ret;

  /* BASE 64 decode the ciphertext */
  ciphertext.assign((std::string)DecodeBase64(ciphertext));
  ciphertext_len = ciphertext.length();

  /* Create and initialise the context */
  EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);

  /* Initialise the decryption operation. */
  if (!EVP_DecryptInit_ex(ctx.get(), EVP_aes_256_gcm(), NULL, NULL, NULL))
    abort();

  plaintext.resize(ciphertext.size());

  /* Set IV length. Not necessary if this is 12 bytes (96 bits) */
  if (!EVP_CIPHER_CTX_ctrl(ctx.get(), EVP_CTRL_GCM_SET_IVLEN, iv_len, NULL))
    abort();

  /* Initialise key and IV */
  if (!EVP_DecryptInit_ex(ctx.get(), NULL, NULL, key->secret, iv)) abort();

  /*
   * Provide any AAD data. This can be called zero or more times as
   * required
   */
  if (!EVP_DecryptUpdate(ctx.get(), NULL, &len, (byte *)&aad[0],
                         (int)aad.size()))
    abort();

  /*
   * Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if (!EVP_DecryptUpdate(ctx.get(), (byte *)&plaintext[0], &len,
                         (const byte *)&ciphertext[0], ciphertext_len))
    abort();
  plaintext_len = len;

  /* Set expected tag value. Works in OpenSSL 1.0.1d and later */
  if (!EVP_CIPHER_CTX_ctrl(ctx.get(), EVP_CTRL_GCM_SET_TAG, 16, tag)) abort();

  /*
   * Finalise the decryption. A positive return value indicates success,
   * anything else is a failure - the plaintext is not trustworthy.
   */
  ret = EVP_DecryptFinal_ex(ctx.get(), (byte *)&plaintext[0] + len, &len);

  if (ret > 0) {
    /* Success */
    plaintext_len += len;
    return plaintext_len;
  } else {
    /* Verify failed */
    return -1;
  }
}