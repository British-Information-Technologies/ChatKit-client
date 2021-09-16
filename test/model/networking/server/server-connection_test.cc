#include "model/networking/server/server-connection.h"

#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <netdb.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <pthread.h>

#include <nlohmann/json.hpp>

#include "model/message-functionality/client-stream-out/send-message-command.h"
#include "model/message-functionality/general/invalid-command.h"
#include "model/message-functionality/network-stream-in/got-info-command.h"
#include "model/message-functionality/network-stream-out-factory.h"
#include "model/message-functionality/network-stream-out/info-command.h"
#include "model/networking/utility/base64.h"
#include "model/networking/utility/elliptic-curve-diffiehellman.h"

using namespace model_networking_utility;
using namespace model_message_functionality;
using namespace model_message_functionality_client_stream_out;
using namespace model_message_functionality_network_stream_out;
using namespace model_message_functionality_network_stream_in;
using namespace model_message_functionality_general;

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

    if ((rv = getaddrinfo(server_ip.c_str(), server_port.c_str(), &hints,
                          &servinfo)) != 0) {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      GTEST_FAIL();
      exit(1);
    }

    // loop through all the results and bind to the first we can
    if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
                         servinfo->ai_protocol)) == -1) {
      perror("server: socket");
      GTEST_FAIL();
      exit(1);
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
    }

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

/* TESTS */
TEST_F(ServerConnectionTest, CreateConnectionTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  EXPECT_NE(server.CreateConnection(), -1);
}

TEST_F(ServerConnectionTest, SendMessageNoKeyTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listener_id, NULL);

  InfoCommand message;

  std::string plaintext = message.ToString();

  int sent_bytes = server.SendMessage(plaintext);
  EXPECT_GT(sent_bytes, 0);
}

TEST_F(ServerConnectionTest, SendWrongMessageNoKeyTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listener_id, NULL);

  std::string to = "mitch";
  std::string content = "test test test";
  SendMessageCommand message(to, content);

  std::string plaintext = message.ToString();

  int sent_bytes = server.SendMessage(plaintext);
  EXPECT_EQ(sent_bytes, 0);
}

TEST_F(ServerConnectionTest, SendInvalidMessageTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listener_id, NULL);

  std::string plaintext =
      "this is a very very very very very very very longgggggggg test!";

  EXPECT_EQ(server.SendMessage(plaintext), 0);
}

TEST_F(ServerConnectionTest, SendEmptyMessageTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listener_id, NULL);

  std::string plaintext = "";

  EXPECT_EQ(server.SendMessage(plaintext), 0);
}

TEST_F(ServerConnectionTest, SendPublicKeyTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listener_id, NULL);

  int sent_bytes = server.SendPublicKey();

  EXPECT_GT(sent_bytes, 0);
}

TEST_F(ServerConnectionTest, EstablishSecureConnectionTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listener_id, NULL);

  EVP_PKEY_free_ptr key_pair = GenerateKeyPair();
  EVP_PKEY_free_ptr public_key = ExtractPublicKey(key_pair.get());

  std::string key_string = SerializePublicKey(key_pair.get());

  NetworkStreamOutFactory factory;
  std::unique_ptr<Message> message = factory.GetMessage(key_string);

  int res = server.EstablishSecureConnection(message.get());

  EXPECT_EQ(res, 1);
}

TEST_F(ServerConnectionTest, FailEstablishSecureConnectionTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);

  EVP_PKEY_free_ptr key_pair = GenerateKeyPair();
  EVP_PKEY_free_ptr public_key = ExtractPublicKey(key_pair.get());

  std::string key_string = SerializePublicKey(key_pair.get());

  NetworkStreamOutFactory factory;
  std::unique_ptr<Message> message = factory.GetMessage(key_string);

  int res = server.EstablishSecureConnection(message.get());

  EXPECT_EQ(res, -1);

  server.CreateConnection();
  pthread_join(listener_id, NULL);
}

TEST_F(ServerConnectionTest, TranslateMessageNoKeyTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listener_id, NULL);

  std::string name = "test";
  std::string owner = "mitch";
  GotInfoCommand message(name, owner);
  std::string serial_message = message.ToString();

  std::string encoded_message = EncodeBase64(serial_message);

  std::unique_ptr<Message> result = server.TranslateMessage(encoded_message);

  EXPECT_EQ(result->ToString().length(), message.ToString().length());

  EXPECT_EQ(result->ToString(), message.ToString());
}

TEST_F(ServerConnectionTest, InvalidTranslateMessageNoKeyTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listener_id, NULL);

  InfoCommand message;
  std::string serial_message = message.ToString();

  std::string encoded_message = EncodeBase64(serial_message);

  std::unique_ptr<Message> result = server.TranslateMessage(encoded_message);

  EXPECT_NE(result->ToString(), message.ToString());

  InvalidCommand invalid;
  EXPECT_EQ(result->ToString(), invalid.ToString());
}

TEST_F(ServerConnectionTest, InvalidTranslateMessageNoKeyNoBase64Test) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listener_id, NULL);

  InfoCommand message;
  std::string serial_message = message.ToString();

  std::unique_ptr<Message> result = server.TranslateMessage(serial_message);

  EXPECT_NE(result->ToString(), message.ToString());

  InvalidCommand invalid;
  EXPECT_EQ(result->ToString(), invalid.ToString());
}

TEST_F(ServerConnectionTest, TranslateMessageNoKeyNoBase64Test) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listener_id, NULL);

  std::string name = "test";
  std::string owner = "mitch";
  GotInfoCommand message(name, owner);
  std::string serial_message = message.ToString();

  std::unique_ptr<Message> result = server.TranslateMessage(serial_message);

  EXPECT_NE(result->ToString(), message.ToString());

  InvalidCommand invalid;
  EXPECT_EQ(result->ToString(), invalid.ToString());
}

TEST_F(ServerConnectionTest, TranslateMessageKeyNoEncryptTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listener_id, NULL);

  EVP_PKEY_free_ptr key_pair = GenerateKeyPair();
  EVP_PKEY_free_ptr public_key = ExtractPublicKey(key_pair.get());

  std::string key_string = SerializePublicKey(key_pair.get());

  NetworkStreamOutFactory factory;
  std::unique_ptr<Message> message = factory.GetMessage(key_string);

  int res = server.EstablishSecureConnection(message.get());

  EXPECT_EQ(res, 1);

  json json_message = {{"type", "UserMessage"},
                       {"from", "mitch"},
                       {"content", "hey this is my cool test!"}};

  std::string json_string = json_message.dump();

  std::string encoded_message = EncodeBase64(json_string);

  std::unique_ptr<Message> result = server.TranslateMessage(encoded_message);

  EXPECT_NE(result->ToString(), json_string);

  InvalidCommand invalid;
  EXPECT_EQ(result->ToString(), invalid.ToString());
}

TEST_F(ServerConnectionTest, TranslateMessageKeyNoBase64NoEncryptTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listener_id, NULL);

  EVP_PKEY_free_ptr key_pair = GenerateKeyPair();
  EVP_PKEY_free_ptr public_key = ExtractPublicKey(key_pair.get());

  std::string key_string = SerializePublicKey(key_pair.get());

  NetworkStreamOutFactory factory;
  std::unique_ptr<Message> message = factory.GetMessage(key_string);

  int res = server.EstablishSecureConnection(message.get());

  EXPECT_EQ(res, 1);

  json json_message = {{"type", "UserMessage"},
                       {"from", "mitch"},
                       {"content", "hey this is my cool test!"}};

  std::string json_string = json_message.dump();

  std::unique_ptr<Message> result = server.TranslateMessage(json_string);

  EXPECT_NE(result->ToString(), json_string);

  InvalidCommand invalid;
  EXPECT_EQ(result->ToString(), invalid.ToString());
}