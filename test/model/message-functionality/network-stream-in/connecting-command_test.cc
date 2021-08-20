#include "model/message-functionality/network-stream-in/connecting-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_network_stream_in;
using json = nlohmann::json;

TEST(ConnectingCommandTest, ToStringTest) {
  ConnectingCommand command;

  EXPECT_EQ(command.ToString(), "{\"type\":\"Connecting\"}");
}

TEST(ConnectingCommandTest, ToJsonTest) {
  ConnectingCommand command;

  json json_object = {{"type", "Connecting"}};

  EXPECT_EQ(command.ToJson(), json_object);
}