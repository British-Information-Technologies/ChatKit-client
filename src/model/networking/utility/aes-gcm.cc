#include "aes-gcm.h"

#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <string.h>

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

  /* BASE 64 encode the ciphertext
   * FIX CMAKE WITH GOOGLE TEST DOWNLOAD LIKE JSON */
  unsigned int input_size = ciphertext.length();
  unsigned int adjustment = ((input_size % 3) ? (3 - (input_size % 3)) : 0);
  unsigned int code_padded_size = ((input_size + adjustment) / 3) * 4;
  unsigned int newline_size = ((code_padded_size) / 72) * 2;
  unsigned int total_size = code_padded_size + newline_size;

  char encoded_data[total_size + 1];
  EVP_EncodeBlock((unsigned char *)encoded_data,
                  (const unsigned char *)ciphertext.c_str(),
                  ciphertext.length());
  encoded_data[total_size] = '\0';

  ciphertext.assign(encoded_data);
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

  std::cout << "ciphertext = " << ciphertext << std::endl;

  /* BASE 64 decode the ciphertext */
  secure_string possible_padding = ciphertext.substr(ciphertext_len - 2, 2);
  unsigned int padding_count = 0;
  for (int index = 0; index < ciphertext_len; ++index) {
    if (ciphertext[index] == '=') ++padding_count;
  }

  unsigned int total_size = (3 * (ciphertext_len / 4)) - padding_count;

  char decoded_data[total_size + 1];
  EVP_DecodeBlock((unsigned char *)decoded_data,
                  (const unsigned char *)ciphertext.c_str(), ciphertext_len);
  decoded_data[total_size] = '\0';

  ciphertext.assign(decoded_data);
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