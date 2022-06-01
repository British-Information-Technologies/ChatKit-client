#include "model/networking/server/server-connection.h"

#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <netdb.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <pthread.h>

#include <nlohmann/json.hpp>

#include "../temporary-server.h"
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

  TemporaryServer *listen_server;

  void SetUp() override {
    listen_server = new TemporaryServer(server_ip, server_port);

    int result = listen_server->SetUp();

    if (result  != 1) {
      fprintf(stderr, "server: setup failed\n");
      exit(1);
    }
  }

  void TearDown() override {
    listen_server->TearDown();

    free(listen_server);
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
  pthread_join(listen_server->listener_id, NULL);

  InfoCommand message;

  std::string plaintext = message.ToString();

  int sent_bytes = server.SendMessage(plaintext);

  std::cout << "message: " << plaintext << std::endl;
  std::cout << "size: " << sent_bytes << std::endl;
  
  EXPECT_GT(sent_bytes, 0);
}

TEST_F(ServerConnectionTest, SendWrongMessageNoKeyTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listen_server->listener_id, NULL);

  std::string to = "mitch";
  std::string content = "test test test";
  SendMessageCommand message(to, content);

  std::string plaintext = message.ToString();

  int sent_bytes = server.SendMessage(plaintext);

  std::cout << "message: " << plaintext << std::endl;
  std::cout << "size: " << sent_bytes << std::endl;

  EXPECT_EQ(sent_bytes, 0);
}

TEST_F(ServerConnectionTest, SendInvalidMessageTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listen_server->listener_id, NULL);

  std::string plaintext =
      "this is a very very very very very very very longgggggggg test!";

  EXPECT_EQ(server.SendMessage(plaintext), 0);
}

TEST_F(ServerConnectionTest, SendEmptyMessageTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listen_server->listener_id, NULL);

  std::string plaintext = "";

  EXPECT_EQ(server.SendMessage(plaintext), 0);
}

TEST_F(ServerConnectionTest, SendPublicKeyTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listen_server->listener_id, NULL);

  int sent_bytes = server.SendPublicKey();

  std::cout << "size:" << sent_bytes << std::endl;

  EXPECT_GT(sent_bytes, 0);
}

TEST_F(ServerConnectionTest, EstablishSecureConnectionTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listen_server->listener_id, NULL);

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
  pthread_join(listen_server->listener_id, NULL);
}

TEST_F(ServerConnectionTest, TranslateMessageNoKeyTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listen_server->listener_id, NULL);

  std::string name = "test";
  std::string owner = "mitch";
  GotInfoCommand message(name, owner);
  std::string serial_message = message.ToString();

  std::cout << "serial message: " << serial_message << std::endl;

  std::string encoded_message = EncodeBase64(serial_message);
  
  std::cout << "encoded message: " << encoded_message << std::endl;

  std::unique_ptr<Message> result = server.TranslateMessage(encoded_message);

  EXPECT_EQ(result->ToString().length(), message.ToString().length());

  EXPECT_EQ(result->ToString(), message.ToString());
}

TEST_F(ServerConnectionTest, InvalidTranslateMessageNoKeyTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listen_server->listener_id, NULL);

  InfoCommand message;
  std::string serial_message = message.ToString();

  std::cout << "serial message: " << serial_message << std::endl;

  std::string encoded_message = EncodeBase64(serial_message);

  std::cout << "encoded message: " << encoded_message << std::endl;

  std::unique_ptr<Message> result = server.TranslateMessage(encoded_message);

  EXPECT_NE(result->ToString(), message.ToString());

  InvalidCommand invalid;
  EXPECT_EQ(result->ToString(), invalid.ToString());
}

TEST_F(ServerConnectionTest, InvalidTranslateMessageNoKeyNoBase64Test) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listen_server->listener_id, NULL);

  InfoCommand message;
  std::string serial_message = message.ToString();

  std::cout << "serial message: " << serial_message << std::endl;

  std::unique_ptr<Message> result = server.TranslateMessage(serial_message);

  EXPECT_NE(result->ToString(), message.ToString());

  InvalidCommand invalid;
  EXPECT_EQ(result->ToString(), invalid.ToString());
}

TEST_F(ServerConnectionTest, TranslateMessageNoKeyNoBase64Test) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listen_server->listener_id, NULL);

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
  pthread_join(listen_server->listener_id, NULL);

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

  std::cout << "serial message: " << json_string << std::endl;

  std::string encoded_message = EncodeBase64(json_string);

  std::cout << "encoded message: " << encoded_message << std::endl;

  std::unique_ptr<Message> result = server.TranslateMessage(encoded_message);

  std::cout << "result message: " << result->ToString() << std::endl;

  EXPECT_NE(result->ToString(), json_string);

  InvalidCommand invalid;
  EXPECT_EQ(result->ToString(), invalid.ToString());
}

TEST_F(ServerConnectionTest, TranslateMessageKeyNoBase64NoEncryptTest) {
  model_networking_server::ServerConnection server(server_ip, server_port);
  server.CreateConnection();
  pthread_join(listen_server->listener_id, NULL);

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

  std::cout << "serial message: " << json_string << std::endl;

  std::unique_ptr<Message> result = server.TranslateMessage(json_string);

  std::cout << "result message: " << result->ToString() << std::endl;

  EXPECT_NE(result->ToString(), json_string);

  InvalidCommand invalid;
  EXPECT_EQ(result->ToString(), invalid.ToString());
}