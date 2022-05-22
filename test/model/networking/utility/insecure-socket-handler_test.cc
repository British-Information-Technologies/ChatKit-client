#include "model/networking/utility/insecure-socket-handler.h"

#include <gtest/gtest.h>

#include <iostream>

#include "../temporary-client.h"
#include "../temporary-server.h"
#include "model/message-functionality/client-stream-out/update-command.h"
#include "model/message-functionality/general/invalid-command.h"
#include "model/networking/utility/base64.h"

#define IP "localhost"
#define PORT "3490"

using namespace model_networking_utility;
using namespace model_message_functionality_client_stream_out;
using namespace model_message_functionality_general;

class InsecureSocketHandlerTest : public ::testing::Test {
 protected:
  TemporaryServer *server;
  TemporaryClient *client;
  InsecureSocketHandler *client_handler;
  InsecureSocketHandler *server_handler;

  void SetUp() override {
    server = new TemporaryServer(IP, PORT);
    client = new TemporaryClient(IP, PORT);

    server->SetUp();
    int client_sockfd = client->setup();
    pthread_join(server->listener_id, NULL);

    client_handler = new InsecureSocketHandler(client_sockfd);
    server_handler = new InsecureSocketHandler(server->new_fd);
  }

  void TearDown() override {
    server->TearDown();
    client->teardown();

    free(server);
    free(client);
  }
};

TEST_F(InsecureSocketHandlerTest, SendMessageTest) {
  UpdateCommand *message = new UpdateCommand;

  int sent_bytes = client_handler->Send(message);
  EXPECT_GT(sent_bytes, 0);
}

TEST_F(InsecureSocketHandlerTest, SendManyMessagesTest) {
  UpdateCommand *message = new UpdateCommand;

  for (int i = 0; i < 250; ++i) {
    int sent_bytes = client_handler->Send(message);
    EXPECT_GT(sent_bytes, 0);
  }
}

TEST_F(InsecureSocketHandlerTest, SendInvalidMessagesTest) {
  InvalidCommand *message = new InvalidCommand;

  for (int i = 0; i < 250; ++i) {
    int sent_bytes = client_handler->Send(message);
    EXPECT_EQ(sent_bytes, 0);
  }
}

TEST_F(InsecureSocketHandlerTest, ReadMessageTest) {
  UpdateCommand *message = new UpdateCommand;

  std::string plaintext = message->ToString();

  std::string encoded_data = EncodeBase64(plaintext);

  std::string result = client_handler->Recv(encoded_data);
  EXPECT_EQ(result, message->ToString());
}

TEST_F(InsecureSocketHandlerTest, ReadManyMessagesTest) {
  UpdateCommand *message = new UpdateCommand;

  std::string plaintext = message->ToString();

  for (int i = 0; i < 250; ++i) {
    std::string encoded_data = EncodeBase64(plaintext);

    std::string result = client_handler->Recv(encoded_data);
    EXPECT_EQ(result, message->ToString());
  }
}