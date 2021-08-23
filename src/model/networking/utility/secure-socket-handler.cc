#include "secure-socket-handler.h"

#include <openssl/err.h>
#include <openssl/rand.h>

#include <nlohmann/json.hpp>

#include "aes-gcm.h"
#include "base64.h"

using namespace networking_utility;
using json = nlohmann::json;

SecureSocketHandler::SecureSocketHandler(int sockfd, DerivedData *key)
    : SocketHandler(sockfd) {
  this->key = key;
}

SecureSocketHandler::~SecureSocketHandler() { delete key; }

int SecureSocketHandler::send(secure_string &plaintext) {
  if (plaintext.length() <= 0) return 0;

  /*Encrypt the message with the key, aad, and iv (faked values) */
  secure_string aad = "address:port";

  const int iv_size = 12;
  byte iv[iv_size + 1];

  int rc = RAND_bytes(iv, iv_size);
  unsigned long err = ERR_get_error();
  if (rc != 1) {
    /* show error */
    return 0;
  }
  iv[iv_size] = '\0';

  const int tag_size = 16;
  byte tag[tag_size + 1];
  tag[tag_size] = '\0';

  /*Format the message into a json string (serialize)*/
  json json_object = {{"message", plaintext}};
  std::string message = json_object.dump();

  plaintext.assign(message);

  secure_string ciphertext;
  aes_gcm_encrypt(plaintext, aad, key, iv, iv_size, ciphertext, tag);

  /* BASE 64 encode the ciphertext */
  ciphertext.assign((std::string)EncodeBase64(ciphertext));

  /*Send message*/
  return writer->write_line((std::string)ciphertext);
}

secure_string SecureSocketHandler::recv() {
  secure_string payload = (secure_string)reader->read_line();

  /* BASE 64 decode the ciphertext */
  payload.assign((std::string)DecodeBase64(payload));

  /* faked values */
  secure_string aad = "address:port";
  const int iv_size = 12;
  byte iv[] = "bbbbbbbbbbbb\0";

  byte tag[16 + 1];

  // aes decrypt
  secure_string decryptedtext;
  aes_gcm_decrypt(payload, payload.length(), aad, tag, key, iv,
                  strlen((char *)iv), decryptedtext);

  return decryptedtext;
}
