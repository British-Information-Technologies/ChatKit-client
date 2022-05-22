#include <gtest/gtest.h>

#include <iostream>

#include "../temporary-client.h"
#include "../temporary-server.h"
#include "model/networking/utility/buffer-reader.h"
#include "model/networking/utility/buffer-writer.h"

#define IP "localhost"
#define PORT "3490"

using namespace model_networking_utility;

class BufferWriterTest : public ::testing::Test {
 protected:
  TemporaryServer *server;
  TemporaryClient *client;
  BufferReader *server_reader;
  BufferWriter *client_writer;

  void SetUp() override {
    server = new TemporaryServer(IP, PORT);
    client = new TemporaryClient(IP, PORT);

    server->SetUp();
    int client_sockfd = client->setup();
    pthread_join(server->listener_id, NULL);

    server_reader = new BufferReader(server->new_fd);
    client_writer = new BufferWriter(client_sockfd);
  }

  void TearDown() override {
    server->TearDown();
    client->teardown();

    free(server);
    free(client);
  }
};

TEST_F(BufferWriterTest, SendAndReadManyMessagesTest) {
  std::string message = "success";

  for (int i = 0; i < 250; ++i) {
    client_writer->WriteLine(message);
  }

  for (int i = 0; i < 250; ++i) {
    std::string result = server_reader->ReadLine();
    EXPECT_EQ(message, result);
  }
}