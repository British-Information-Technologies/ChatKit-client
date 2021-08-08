#include "model/networking/server/server-connection.h"

#include <arpa/inet.h>
#include <errno.h>
#include <gtest/gtest.h>
#include <netdb.h>
#include <netinet/in.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <nlohmann/json.hpp>

#include "model/networking/utility/aes-gcm.h"
#include "model/networking/utility/elliptic-curve-diffiehellman.h"
#include "model/networking/utility/memory-manager.h"
#include "model/networking/utility/sha-3-256.h"

using namespace networking_server;
using namespace networking_utility;
using json = nlohmann::json;

#define BACKLOG 1  // how many pending connections queue will hold

class ServerConnectionTest : public ::testing::Test {
 protected:
  std::string server_ip = "localhost";
  std::string server_port = "3490";
  DerivedData *key;

  pthread_t listener_id;
  int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
  socklen_t sin_size;
  struct sockaddr_storage their_addr;  // connector's address information
  char s[INET6_ADDRSTRLEN];

  void SetUp() override {
    struct addrinfo hints, *servinfo, *p;
    int yes = 1;
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;  // use my IP

    // if ((rv = getaddrinfo(NULL, server_port.c_str(), &hints, &servinfo)) !=
    // 0) {
    if ((rv = getaddrinfo(server_ip.c_str(), server_port.c_str(), &hints,
                          &servinfo)) != 0) {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      GTEST_FAIL();
      exit(1);
    }

    // loop through all the results and bind to the first we can
    // for (p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
                         servinfo->ai_protocol)) == -1) {
      perror("server: socket");
      GTEST_FAIL();
      exit(1);
      // continue;
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
      perror("setsockopt");
      GTEST_FAIL();
      exit(1);
    }

    if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
      close(sockfd);
      perror("server: bind");
      GTEST_FAIL();
      exit(1);
      // continue;
    }

    // break;
    // }

    freeaddrinfo(servinfo);  // all done with this structure

    if (p == NULL) {
      fprintf(stderr, "server: failed to bind\n");
      GTEST_FAIL();
      exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
      perror("listen");
      GTEST_FAIL();
      exit(1);
    }

    /* Listen on a thread so test can still occur */
    pthread_create(&listener_id, NULL,
                   &ServerConnectionTest::ListenForConnectionWrapper, this);
  }

  void TearDown() override {
    pthread_join(listener_id, NULL);

    free(key->secret);
    free(key);

    close(sockfd);
    close(new_fd);
  }

  static void *ListenForConnectionWrapper(void *context) {
    return ((ServerConnectionTest *)context)->ListenForConnection();
  }

  void *ListenForConnection(void) {
    printf("server: waiting for connection...\n");

    sin_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    if (new_fd == -1) {
      perror("accept");
      exit(1);
    }

    inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr),
              s, sizeof s);
    printf("server: got connection from %s\n", s);

    Exchange();

    return 0;
  }

  // get sockaddr, IPv4 or IPv6:
  void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
      return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
  }

  void Exchange() {
    EVP_PKEY_free_ptr key_pair = GenerateKeyPair();
    EVP_PKEY_free_ptr public_key = ExtractPublicKey(key_pair.get());

    /*public keys need to be shared with other party at this point*/
    std::string serial_public_key =
        SerializePublicKey(public_key.get()).append("\n");

    int sent_bytes =
        send(new_fd, serial_public_key.c_str(), serial_public_key.length(), 0);

    int buffer_size = 1024;
    char buffer[buffer_size];
    int bytes_read = recv(new_fd, buffer, buffer_size - 1, 0);
    *(buffer + buffer_size) = '\0';

    EVP_PKEY_free_ptr peer_public_key = DeserializePublicKey(buffer);

    /*Create the shared secret with other users public key and your
      own private key (this has wrong public key as a place holder*/
    key = DeriveSharedSecret(peer_public_key.get(), key_pair.get());

    /*Hash the secret to create the key*/
    HashData(key);
  }
};

/* TESTS */
TEST_F(ServerConnectionTest, CreateConnectionTest) {
  ServerConnection server;
  EXPECT_TRUE(server.create_connection(server_ip, server_port));
}

TEST_F(ServerConnectionTest, SendShortMessageTest) {
  ServerConnection server;
  server.create_connection(server_ip, server_port);

  secure_string plaintext = "this is a test";

  EXPECT_GT(server.send_message(plaintext),
            0);  // There should be more than 0 bytes sent.

  int buffer_size = 1024;
  char buffer[buffer_size];
  int bytes_read = recv(new_fd, buffer, buffer_size - 1, 0);
  *(buffer + buffer_size - 1) = '\0';

  std::cout << "server read: " << buffer << std::endl;

  EXPECT_GT(bytes_read,
            0);  // There should be more than 0 bytes read by the server.

  secure_string tmp;
  tmp.assign(buffer);
  json json_object = json::parse(tmp);

  std::cout << "json object: " << json_object << std::endl;

  std::string encrypted_message = json_object["message"];

  EXPECT_STRNE(encrypted_message.c_str(), plaintext.c_str());

  EXPECT_NE(plaintext.length(), encrypted_message.length());
}

TEST_F(ServerConnectionTest, SendShortMessageDecryptTest) {
  ServerConnection server;
  server.create_connection(server_ip, server_port);
  pthread_join(listener_id, NULL);

  secure_string plaintext = "this is a test";

  EXPECT_GT(server.send_message(plaintext),
            0);  // There should be more than 0 bytes sent.

  int buffer_size = 1024;
  char buffer[buffer_size];
  int bytes_read = recv(new_fd, buffer, buffer_size - 1, 0);
  *(buffer + buffer_size - 1) = '\0';

  std::cout << "server read: " << buffer << std::endl;

  EXPECT_GT(bytes_read,
            0);  // There should be more than 0 bytes read by the server.

  secure_string tmp;
  tmp.assign(buffer);
  json json_object = json::parse(tmp);

  std::cout << "json object: " << json_object << std::endl;

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

  EXPECT_STRNE(encrypted_message.c_str(), plaintext.c_str());

  EXPECT_NE(plaintext.length(), encrypted_message.length());

  secure_string decryptedtext;
  aes_gcm_decrypt(encrypted_message, encrypted_message.length(), aad, tag, key,
                  iv, strlen((char *)iv), decryptedtext);

  std::cout << "encrypted: " << encrypted_message << std::endl;
  std::cout << "decrypted: " << decryptedtext << std::endl;
  std::cout << "plaintext: " << decryptedtext << std::endl;

  EXPECT_STREQ(decryptedtext.c_str(), plaintext.c_str());
}

TEST_F(ServerConnectionTest, SendLongMessageDecryptTest) {
  ServerConnection server;
  server.create_connection(server_ip, server_port);
  pthread_join(listener_id, NULL);

  secure_string plaintext =
      "this is a very very very very very very very longgggggggg test! But a "
      "dsasadasdasdsa sdadasdklaskflkslfkalfkla";

  EXPECT_GT(server.send_message(plaintext),
            0);  // There should be more than 0 bytes sent.

  int buffer_size = 1024;
  char buffer[buffer_size];
  int bytes_read = recv(new_fd, buffer, buffer_size - 1, 0);
  *(buffer + buffer_size - 1) = '\0';

  std::cout << "server read: " << buffer << std::endl;

  EXPECT_GT(bytes_read,
            0);  // There should be more than 0 bytes read by the server.

  secure_string tmp;
  tmp.assign(buffer);
  json json_object = json::parse(tmp);

  std::cout << "json object: " << json_object << std::endl;

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

  EXPECT_STRNE(encrypted_message.c_str(), plaintext.c_str());

  EXPECT_NE(plaintext.length(), encrypted_message.length());

  secure_string decryptedtext;
  aes_gcm_decrypt(encrypted_message, encrypted_message.length(), aad, tag, key,
                  iv, strlen((char *)iv), decryptedtext);

  std::cout << "encrypted: " << encrypted_message << std::endl;
  std::cout << "decrypted: " << decryptedtext << std::endl;
  std::cout << "plaintext: " << decryptedtext << std::endl;

  EXPECT_STREQ(decryptedtext.c_str(), plaintext.c_str());
}

TEST_F(ServerConnectionTest, SendEmptyMessageTest) {
  ServerConnection server;
  server.create_connection(server_ip, server_port);
  pthread_join(listener_id, NULL);

  secure_string plaintext = "";

  EXPECT_EQ(server.send_message(plaintext), 0);

  // No message should be sent, so 0 zero bytes should be returned
}

TEST_F(ServerConnectionTest, ReadShortMessageTest) {
  ServerConnection server;
  server.create_connection(server_ip, server_port);
  pthread_join(listener_id, NULL);

  secure_string plaintext = "this is a test";

  secure_string aad = "address:port";  // faked value
  const int iv_size = 12;
  byte iv[iv_size + 1];

  int rc = RAND_bytes(iv, iv_size);
  unsigned long err = ERR_get_error();
  if (rc != 1) {
    FAIL();
  }
  iv[iv_size] = '\0';

  const int tag_size = 16;
  byte tag[tag_size + 1];
  tag[tag_size] = '\0';

  secure_string ciphertext;
  int ciphertext_len =
      aes_gcm_encrypt(plaintext, aad, key, iv, iv_size, ciphertext, tag);

  json json_object = {
      {"message", ciphertext}, {"aad", aad}, {"iv", iv}, {"tag", tag}};
  std::string message = json_object.dump();
  message.append("\n");

  EXPECT_EQ(send(new_fd, message.c_str(), message.length(), 0),
            message.length());

  secure_string result = server.read_message();

  std::cout << "server read: " << result << std::endl;

  EXPECT_EQ(result.length(), plaintext.length());

  EXPECT_STREQ(result.c_str(), plaintext.c_str());
}

TEST_F(ServerConnectionTest, ReadLongMessageTest) {
  ServerConnection server;
  server.create_connection(server_ip, server_port);
  pthread_join(listener_id, NULL);

  secure_string plaintext =
      "this is a test for a very long message, however, its not longer than "
      "the buffer which will be important!";

  secure_string aad = "address:port";  // faked value
  const int iv_size = 12;
  byte iv[iv_size + 1];

  int rc = RAND_bytes(iv, iv_size);
  unsigned long err = ERR_get_error();
  if (rc != 1) {
    FAIL();
  }
  iv[iv_size] = '\0';

  const int tag_size = 16;
  byte tag[tag_size + 1];
  tag[tag_size] = '\0';

  secure_string ciphertext;
  int ciphertext_len =
      aes_gcm_encrypt(plaintext, aad, key, iv, iv_size, ciphertext, tag);

  json json_object = {
      {"message", ciphertext}, {"aad", aad}, {"iv", iv}, {"tag", tag}};
  std::string message = json_object.dump();
  message.append("\n");

  EXPECT_EQ(send(new_fd, message.c_str(), message.length(), 0),
            message.length());

  secure_string result = server.read_message();

  std::cout << "server read: " << result << std::endl;

  EXPECT_EQ(result.length(), plaintext.length());

  EXPECT_STREQ(result.c_str(), plaintext.c_str());
}

TEST_F(ServerConnectionTest, ReadBufferSizeMessageTest) {
  ServerConnection server;
  server.create_connection(server_ip, server_port);
  pthread_join(listener_id, NULL);

  secure_string plaintext = "this is pp";

  secure_string aad = "address:port";  // faked value
  const int iv_size = 12;
  byte iv[iv_size + 1];

  int rc = RAND_bytes(iv, iv_size);
  unsigned long err = ERR_get_error();
  if (rc != 1) {
    FAIL();
  }
  iv[iv_size] = '\0';

  const int tag_size = 16;
  byte tag[tag_size + 1];
  tag[tag_size] = '\0';

  secure_string ciphertext;
  int ciphertext_len =
      aes_gcm_encrypt(plaintext, aad, key, iv, iv_size, ciphertext, tag);

  json json_object = {
      {"message", ciphertext}, {"aad", aad}, {"iv", iv}, {"tag", tag}};
  std::string message = json_object.dump();
  message.append("\n");

  EXPECT_EQ(send(new_fd, message.c_str(), message.length(), 0),
            message.length());

  secure_string result = server.read_message();

  std::cout << "server read: " << result << std::endl;

  EXPECT_EQ(result.length(), plaintext.length());

  EXPECT_STREQ(result.c_str(), plaintext.c_str());
}

TEST_F(ServerConnectionTest, ReadMultipleSmallMessageTest) {
  ServerConnection server;
  server.create_connection(server_ip, server_port);
  pthread_join(listener_id, NULL);

  secure_string aad = "address:port";  // faked value
  const int iv_size = 12;
  byte iv[iv_size + 1];

  int rc = RAND_bytes(iv, iv_size);
  unsigned long err = ERR_get_error();
  if (rc != 1) {
    FAIL();
  }
  iv[iv_size] = '\0';

  const int tag_size = 16;
  byte tag[tag_size + 1];
  tag[tag_size] = '\0';

  secure_string plaintext_first = "first";
  secure_string plaintext_second = "second";

  secure_string ciphertext_first;
  secure_string ciphertext_second;

  aes_gcm_encrypt(plaintext_first, aad, key, iv, iv_size, ciphertext_first,
                  tag);

  json json_object_first = {
      {"message", ciphertext_first}, {"aad", aad}, {"iv", iv}, {"tag", tag}};

  std::string message_first = json_object_first.dump();

  message_first.append("\n");

  EXPECT_EQ(send(new_fd, message_first.c_str(), message_first.length(), 0),
            message_first.length());

  secure_string result_one = server.read_message();

  std::cout << "server read: " << result_one << std::endl;

  EXPECT_EQ(result_one.length(), plaintext_first.length());

  EXPECT_STREQ(result_one.c_str(), plaintext_first.c_str());

  aes_gcm_encrypt(plaintext_second, aad, key, iv, iv_size, ciphertext_second,
                  tag);

  json json_object_second = {
      {"message", ciphertext_second}, {"aad", aad}, {"iv", iv}, {"tag", tag}};

  std::string message_second = json_object_second.dump();
  message_second.append("\n");

  EXPECT_EQ(send(new_fd, message_second.c_str(), message_second.length(), 0),
            message_second.length());

  secure_string result_two = server.read_message();

  std::cout << "server read: " << result_two << std::endl;

  EXPECT_EQ(result_two.length(), plaintext_second.length());

  EXPECT_STREQ(result_two.c_str(), plaintext_second.c_str());
}

TEST_F(ServerConnectionTest, ReadManySmallMessageTest) {
  ServerConnection server;
  server.create_connection(server_ip, server_port);
  pthread_join(listener_id, NULL);

  secure_string plaintext_first = "first";
  int sent_items = 0;
  int read_items = 0;

  secure_string aad = "address:port";  // faked value
  const int iv_size = 12;
  byte iv[iv_size + 1];

  int rc = RAND_bytes(iv, iv_size);
  unsigned long err = ERR_get_error();
  if (rc != 1) {
    FAIL();
  }
  iv[iv_size] = '\0';

  const int tag_size = 16;
  byte tag[tag_size + 1];
  tag[tag_size] = '\0';

  secure_string ciphertext;
  int ciphertext_len =
      aes_gcm_encrypt(plaintext_first, aad, key, iv, iv_size, ciphertext, tag);

  json json_object = {
      {"message", ciphertext}, {"aad", aad}, {"iv", iv}, {"tag", tag}};
  std::string message = json_object.dump();
  message.append("\n");

  for (int i = 0; i < 250; ++i) {
    EXPECT_EQ(send(new_fd, message.c_str(), message.length(), 0),
              message.length());

    ++sent_items;
  }

  for (int i = 0; i < 250; ++i) {
    secure_string result_one = server.read_message();

    std::cout << "server read: " << result_one << std::endl;

    EXPECT_EQ(result_one.length(), plaintext_first.length());

    EXPECT_STREQ(result_one.c_str(), plaintext_first.c_str());

    ++read_items;
  }

  std::cout << "sent items = " << sent_items << std::endl;
  std::cout << "read items = " << read_items << std::endl;
  EXPECT_EQ(sent_items, read_items);
}

TEST_F(ServerConnectionTest, ReadOverflowMessageTest) {
  ServerConnection server;
  server.create_connection(server_ip, server_port);
  pthread_join(listener_id, NULL);

  secure_string plaintext_first =
      "this message must be larger than the buffer of 1024 bytes to ensure the "
      "read method can successfully retrieve messages beyond this bound even "
      "if they overflow out the end! Very very very very very "
      "important!"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaahsj"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaahsj"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaahsj"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaahsj"
      "dshjdhjshdjshdjsdhjshdjhfdsjfdsfkj";

  secure_string aad = "address:port";  // faked value
  const int iv_size = 12;
  byte iv[iv_size + 1];

  int rc = RAND_bytes(iv, iv_size);
  unsigned long err = ERR_get_error();
  if (rc != 1) {
    FAIL();
  }
  iv[iv_size] = '\0';

  const int tag_size = 16;
  byte tag[tag_size + 1];
  tag[tag_size] = '\0';

  secure_string ciphertext;
  int ciphertext_len =
      aes_gcm_encrypt(plaintext_first, aad, key, iv, iv_size, ciphertext, tag);

  json json_object = {
      {"message", ciphertext}, {"aad", aad}, {"iv", iv}, {"tag", tag}};
  std::string message = json_object.dump();
  message.append("\n");

  EXPECT_EQ(send(new_fd, message.c_str(), message.length(), 0),
            message.length());

  secure_string result_one = server.read_message();

  std::cout << "server read: " << result_one << std::endl;

  EXPECT_EQ(result_one.length(), plaintext_first.length());

  EXPECT_STREQ(result_one.c_str(), plaintext_first.c_str());
}
