#include "model/networking/server/server-connection.h"

#include <arpa/inet.h>
// #include <errno.h>
#include <gtest/gtest.h>
#include <netdb.h>
// #include <netinet/in.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <pthread.h>
// #include <signal.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <unistd.h>

#include <nlohmann/json.hpp>

#include "model/message-functionality/client-stream-out/send-message-command.h"
#include "model/message-functionality/message.h"
#include "model/message-functionality/network-stream-in/key-command.h"
#include "model/networking/utility/aes-gcm.h"
#include "model/networking/utility/elliptic-curve-diffiehellman.h"
#include "model/networking/utility/insecure-socket-handler.h"
#include "model/networking/utility/secure-socket-handler.h"
#include "model/networking/utility/sha-3-256.h"
#include "model/networking/utility/socket-handler.h"

using namespace model_networking_utility;
using namespace model_message_functionality;
using namespace model_message_functionality_client_stream_out;
using namespace model_message_functionality_network_stream_in;

using json = nlohmann::json;

#define BACKLOG 1  // how many pending connections queue will hold

class ServerConnectionTest : public ::testing::Test {
 protected:
  std::string server_ip = "localhost";
  std::string server_port = "3490";
  DerivedData *key = nullptr;
  SocketHandler *socket_handler = nullptr;

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

    // if ((rv = getaddrinfo(NULL, server_port.c_str(), &hints, &servinfo))
    // !=
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
    if (key != nullptr) {
      free(key->secret);
      free(key);
    }

    if (socket_handler != nullptr) {
      free(socket_handler);
    }

    close(sockfd);
    close(new_fd);
  }

  void set_state(SocketHandler *next_handler) {
    delete socket_handler;
    socket_handler = next_handler;
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

    return 0;
  }

  // get sockaddr, IPv4 or IPv6:
  void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
      return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
  }
};

// void Exchange() {
//     set_state(new InsecureSocketHandler(new_fd));

//     EVP_PKEY_free_ptr key_pair = GenerateKeyPair();
//     EVP_PKEY_free_ptr public_key = ExtractPublicKey(key_pair.get());

//     /*public keys need to be shared with other party at this point*/
//     std::string serial_public_key = SerializePublicKey(public_key.get());
//     json serial_public_key_json = json::parse(serial_public_key);

//     KeyCommand key_command(serial_public_key_json["key"]);

//     socket_handler->send(&key_command);

//     std::string result = socket_handler->recv();

//     EVP_PKEY_free_ptr peer_public_key = DeserializePublicKey(result.c_str());

//     /*Create the shared secret with other users public key and your
//       own private key (this has wrong public key as a place holder*/
//     key = DeriveSharedSecret(peer_public_key.get(), key_pair.get());

//     /*Hash the secret to create the key*/
//     HashData(key);

//     set_state(new SecureSocketHandler(new_fd, key));
//   }

/* TESTS */
TEST_F(ServerConnectionTest, CreateConnectionTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  EXPECT_NE(server.CreateConnection(), -1);
}

// TEST_F(ServerConnectionTest, SendShortMessageTest) {
//   networking_server::ServerConnection server(server_ip, server_port);
//   server.create_connection();
//   pthread_join(listener_id, NULL);

//   std::string to = "mitch";
//   std::string plaintext = "this is a test";
//   SendMessageCommand message(to, plaintext);

//   plaintext = message.ToString();
//   EXPECT_GT(server.send_message(plaintext),
//             0);  // There should be more than 0 bytes sent.

//   std::string result = socket_handler->recv();

//   EXPECT_GT(result.length(),
//             0);  // There should be more than 0 bytes read.

//   std::cout << "server read: " << result << std::endl;

//   EXPECT_EQ(plaintext, result);

//   EXPECT_EQ(plaintext.length(), result.length());
// }

// TEST_F(ServerConnectionTest, SendLongMessageTest) {
//   networking_server::ServerConnection server(server_ip, server_port);
//   server.create_connection();
//   pthread_join(listener_id, NULL);

//   std::string plaintext =
//       "this is a very very very very very very very longgggggggg test! But a
//       " "dsasadasdasdsa sdadasdklaskflkslfkalfkla";

//   EXPECT_GT(server.send_message(plaintext),
//             0);  // There should be more than 0 bytes sent.

//   std::string result = socket_handler->recv();

//   EXPECT_GT(result.length(),
//             0);  // There should be more than 0 bytes read.

//   std::cout << "server read: " << result << std::endl;

//   EXPECT_EQ(plaintext, result);

//   EXPECT_EQ(plaintext.length(), result.length());
// }

// TEST_F(ServerConnectionTest, SendEmptyMessageTest) {
//   networking_server::ServerConnection server(server_ip, server_port);
//   server.create_connection();
//   pthread_join(listener_id, NULL);

//   std::string plaintext = "";

//   // No message should be sent, so 0 zero bytes should be returned
//   EXPECT_EQ(server.send_message(plaintext), 0);
// }

// TEST_F(ServerConnectionTest, ReadShortMessageTest) {
//   networking_server::ServerConnection server(server_ip, server_port);
//   server.create_connection();
//   pthread_join(listener_id, NULL);

//   std::string plaintext = "this is a test";
//   std::string to = "mitch";
//   SendMessageCommand message(to, plaintext);

//   int sent_bytes = socket_handler->send(&message);

//   EXPECT_NE(sent_bytes, plaintext.length());

//   std::unique_ptr<Message> result = server.read_message();

//   std::cout << "server read: " << result->ToString() << std::endl;

//   EXPECT_EQ(result->ToString().length(), plaintext.length());

//   EXPECT_EQ(result, plaintext);
// }

// TEST_F(ServerConnectionTest, ReadLongMessageTest) {
//   networking_server::ServerConnection server(server_ip, server_port);
//   server.create_connection();
//   pthread_join(listener_id, NULL);

//   std::string plaintext =
//       "this is a test for a very long message, however, its not longer than "
//       "the buffer which will be important!";
//   std::string to = "mitch";
//   SendMessageCommand message(to, plaintext);

//   int sent_bytes = socket_handler->send(&message);

//   EXPECT_NE(sent_bytes, plaintext.length());

//   std::unique_ptr<Message> result = server.read_message();

//   std::cout << "server read: " << result->ToString() << std::endl;

//   EXPECT_EQ(result->ToString().length(), plaintext.length());

//   EXPECT_EQ(result, plaintext);
// }

// TEST_F(ServerConnectionTest, ReadBufferSizeMessageTest) {
//   networking_server::ServerConnection server(server_ip, server_port);
//   server.create_connection();
//   pthread_join(listener_id, NULL);

//   std::string plaintext =
//       "this message is the same length as the buffer, but one char is missing
//       " "for the new line character. but I must say this is still very short,
//       " "I'm going to start copy and pasting to reach a size of 1023 chars
//       now: " "this message is the same length as the buffer, but one char is
//       missing " "for the new line character. but I must say this is still
//       very short, " "I'm going to start copy and pasting to reach a size of
//       1023 chars now: " "this message is the same length as the buffer, but
//       one char is missing " "for the new line character. but I must say this
//       is still very short, " "I'm going to start copy and pasting to reach a
//       size of 1023 chars now: " "this message is the same length as the
//       buffer, but one char is missing " "for the new line character. but I
//       must say this is still very short, " "I'm going to start copy and
//       pasting to reach a size of 1023 chars now: " "this message is the same
//       length as the buffer, but one char is missing " "for the new line
//       character. but I must say this is still very short, " "I'm going to
//       start copy and pasting to ";
//   std::string to = "mitch";
//   SendMessageCommand message(to, plaintext);

//   int sent_bytes = socket_handler->send(&message);

//   EXPECT_NE(sent_bytes, plaintext.length());

//   std::unique_ptr<Message> result = server.read_message();

//   std::cout << "server read: " << result->ToString() << std::endl;

//   EXPECT_EQ(result->ToString().length(), plaintext.length());

//   EXPECT_EQ(result, plaintext);
// }

// TEST_F(ServerConnectionTest, ReadMultipleSmallMessageTest) {
//   networking_server::ServerConnection server(server_ip, server_port);
//   server.create_connection();
//   pthread_join(listener_id, NULL);

//   std::string plaintext_first = "first";
//   std::string to_first = "mitch";
//   SendMessageCommand message_first(to_first, plaintext_first);

//   std::string plaintext_second = "second";
//   std::string to_second = "mitch";
//   SendMessageCommand message_second(to_second, plaintext_second);

//   std::string ciphertext_first;
//   std::string ciphertext_second;

//   int sent_bytes_first = socket_handler->send(&message_first);

//   EXPECT_NE(sent_bytes_first, plaintext_first.length());

//   std::unique_ptr<Message> result_first = server.read_message();

//   std::cout << "server read: " << result_first->ToString() << std::endl;

//   EXPECT_EQ(result_first->ToString().length(), plaintext_first.length());

//   EXPECT_EQ(result_first, plaintext_first);

//   int sent_bytes_second = socket_handler->send(&message_second);

//   EXPECT_NE(sent_bytes_second, plaintext_second.length());

//   std::unique_ptr<Message> result_second = server.read_message();

//   std::cout << "server read: " << result_second->ToString() << std::endl;

//   EXPECT_EQ(result_second->ToString().length(), plaintext_second.length());

//   EXPECT_EQ(result_second, plaintext_second);
// }

// TEST_F(ServerConnectionTest, ReadManySmallMessageTest) {
//   networking_server::ServerConnection server(server_ip, server_port);
//   server.create_connection();
//   pthread_join(listener_id, NULL);

//   std::string plaintext = "first";
//   std::string to = "mitch";
//   SendMessageCommand message(to, plaintext);

//   int sent_items = 0;
//   int read_items = 0;

//   for (int i = 0; i < 250; ++i) {
//     int sent_bytes = socket_handler->send(&message);
//     EXPECT_NE(sent_bytes, plaintext.length());

//     ++sent_items;
//   }

//   for (int i = 0; i < 250; ++i) {
//     std::unique_ptr<Message> result = server.read_message();
//     std::cout << "server read: " << result->ToString() << std::endl;

//     EXPECT_EQ(result->ToString().length(), plaintext.length());
//     EXPECT_EQ(result, plaintext);

//     ++read_items;
//   }

//   std::cout << "sent items = " << sent_items << std::endl;
//   std::cout << "read items = " << read_items << std::endl;
//   EXPECT_EQ(sent_items, read_items);
// }

// TEST_F(ServerConnectionTest, ReadOverflowMessageTest) {
//   networking_server::ServerConnection server(server_ip, server_port);
//   server.create_connection();
//   pthread_join(listener_id, NULL);

//   std::string plaintext =
//       "this message must be larger than the buffer of 1024 bytes to ensure
//       the " "read method can successfully retrieve messages beyond this bound
//       even " "if they overflow out the end! Very very very very very "
//       "important!"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaahsj"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaahsj"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaahsj"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaahsj"
//       "dshjdhjshdjshdjsdhjshdjhfdsjfdsfkj";
//   std::string to = "mitch";
//   SendMessageCommand message(to, plaintext);

//   int sent_bytes = socket_handler->send(&message);

//   EXPECT_NE(sent_bytes, plaintext.length());

//   std::unique_ptr<Message> result = server.read_message();

//   std::cout << "server read: " << result->ToString() << std::endl;

//   EXPECT_EQ(result->ToString().length(), plaintext.length());

//   EXPECT_EQ(result, plaintext);
// }
