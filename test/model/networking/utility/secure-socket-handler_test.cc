#include "model/networking/utility/secure-socket-handler.h"

#include <gtest/gtest.h>

#include <iostream>

#include "../temporary-client.h"
#include "../temporary-server.h"

#define IP "localhost"
#define PORT "3490"

using namespace networking_utility;

class SecureSocketHandlerTest : public ::testing::Test {
 protected:
  TemporaryServer *server;
  TemporaryClient *client;
  SecureSocketHandler *client_handler;
  SecureSocketHandler *server_handler;
  DerivedData *key;

  void SetUp() override {
    server = new TemporaryServer(IP, PORT);
    client = new TemporaryClient(IP, PORT);
    key = (DerivedData *)malloc(sizeof(DerivedData));

    key->length = 256;
    key->secret = (unsigned char *)malloc(key->length);
    key->secret = (unsigned char *)"300EE3B4C88D252280F8972B42EC4605A0499DE55248EC17D08F5CB8AC080B17300EE3B4C88D252280F8972B42EC4605A0499DE55248EC17D08F5CB8AC080B17300EE3B4C88D252280F8972B42EC4605A0499DE55248EC17D08F5CB8AC080B17300EE3B4C88D252280F8972B42EC4605A0499DE55248EC17D08F5CB8AC080B17";

    server->setup();
    int client_sockfd = client->setup();
    pthread_join(server->listener_id, NULL);

    client_handler = new SecureSocketHandler(client_sockfd, key);
    server_handler = new SecureSocketHandler(server->new_fd, key);
  }

  void TearDown() override {
    server->teardown();
    client->teardown();

    free(server);
    free(client);
    free(key);
  }
};

TEST_F(SecureSocketHandlerTest, SendAndReadManyMessagesTest) {
  secure_string message = "pog champ";

  for (int i = 0; i < 250; ++i) {
    client_handler->send(message);
    secure_string result = server_handler->recv();
    // std::cout << result << std::endl;
    EXPECT_EQ(message, result);
  }

  // for (int i = 0; i < 250; ++i) {
  //   secure_string result = server_handler->recv();
  //   // std::cout << result << std::endl;
  //   EXPECT_EQ(message, result);
  // }
}