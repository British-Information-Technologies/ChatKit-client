#include "model/message-functionality/client-stream-in-factory.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality;
using json = nlohmann::json;

TEST(ClientStreamInFactoryTest, GetConnectCommandTest) {
  ClientStreamInFactory factory;

  json json_object = {{"type", "Connect"}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(ClientStreamInFactoryTest, GetDisconnectedCommandTest) {
  ClientStreamInFactory factory;

  json json_object = {{"type", "Disconnected"}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), json_object.dump());
}