#include "model/networking/utility/secure-socket-handler.h"

#include <gtest/gtest.h>

#include "../temporary-client.h"
#include "../temporary-server.h"

#define IP "localhost"
#define PORT "3490"

class SecureSocketHandlerTest : public ::testing::Test {
 protected:
  TemporaryServer *server;
  TemporaryClient *client;

  void SetUp() override {
    server = new TemporaryServer(IP, PORT);
    client = new TemporaryClient(IP, PORT);

    server->setup();
    client->setup();
  }

  void TearDown() override {
    server->teardown();
    client->teardown();

    free(server);
    free(client);
  }
};