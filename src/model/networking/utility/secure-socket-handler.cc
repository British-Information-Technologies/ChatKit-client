#include "secure-socket-handler.h"

#include <openssl/err.h>
#include <openssl/rand.h>

#include <nlohmann/json.hpp>

#include "aes-gcm.h"
#include "base64.h"

using namespace networking_utility;
using namespace chat_client_model_message_functionality;
using json = nlohmann::json;

SecureSocketHandler::SecureSocketHandler(int sockfd, DerivedData *key)
    : SocketHandler(sockfd) {
  this->key = key;
}

SecureSocketHandler::~SecureSocketHandler() { delete key; }

int SecureSocketHandler::send(Message *message) {
  std::string type = message->ToJson()["type"];
  if (type.compare(INVALID) == 0) return 0;

  /*Encrypt the message with the key, aad, and iv (faked values) */
  std::string aad = "address:port";

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
  std::string json_string = message->ToString();

  std::string ciphertext;
  aes_gcm_encrypt(json_string, aad, key, iv, iv_size, ciphertext, tag);

  /* BASE 64 encode the ciphertext */
  ciphertext.assign(EncodeBase64(ciphertext));

  /*Send message*/
  return writer->write_line(ciphertext);
}

std::string SecureSocketHandler::recv() {
  std::string payload = reader->read_line();

  /* BASE 64 decode the ciphertext */
  payload.assign(DecodeBase64(payload));

  /* faked values */
  std::string aad = "address:port";
  const int iv_size = 12;
  byte iv[] = "bbbbbbbbbbbb\0";

  byte tag[16 + 1];

  // aes decrypt
  std::string decryptedtext;
  aes_gcm_decrypt(payload, payload.length(), aad, tag, key, iv,
                  strlen((char *)iv), decryptedtext);

  return decryptedtext;
}
