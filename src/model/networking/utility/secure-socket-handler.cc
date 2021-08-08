#include "secure-socket-handler.h"

#include <openssl/err.h>
#include <openssl/rand.h>

#include <nlohmann/json.hpp>

#include "aes-gcm.h"

using namespace networking_utility;
using json = nlohmann::json;

SecureSocketHandler::SecureSocketHandler(int sockfd, DerivedData *key)
    : SocketHandler(sockfd) {
  this->key = key;
}

SecureSocketHandler::~SecureSocketHandler() { delete key; }

int SecureSocketHandler::send(secure_string &plaintext) {
  if (plaintext.length() <= 0) return 0;

  /*Encrypt the message with the key, aad, and iv*/
  secure_string aad = "address:port";  // faked value
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

  secure_string ciphertext;
  aes_gcm_encrypt(plaintext, aad, key, iv, iv_size, ciphertext, tag);

  /*Format the message into a json string (serialize)*/
  json json_object = {
      {"message", ciphertext}, {"aad", aad}, {"iv", iv}, {"tag", tag}};
  std::string message = json_object.dump();

  /*Send message*/
  return writer->write_line(message);
}

secure_string SecureSocketHandler::recv() {
  secure_string payload = (secure_string)reader->read_line();

  json json_object = json::parse(payload);

  secure_string encrypted_message = json_object["message"];
  secure_string aad = json_object["aad"];
  json tag_object = json_object["tag"];
  json iv_object = json_object["iv"];

  byte tag[tag_object.size() + 1];
  int i = 0;
  for (auto it = tag_object.begin(); it != tag_object.end(); ++it, ++i) {
    tag[i] = it.value();
  }
  tag[tag_object.size()] = '\0';

  byte iv[iv_object.size() + 1];
  i = 0;
  for (auto it = iv_object.begin(); it != iv_object.end(); ++it, ++i) {
    iv[i] = it.value();
  }
  iv[iv_object.size()] = '\0';

  // aes decrypt
  secure_string decryptedtext;
  aes_gcm_decrypt(encrypted_message, encrypted_message.length(), aad, tag, key,
                  iv, strlen((char *)iv), decryptedtext);

  return decryptedtext;
}
