#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include "model/message-functionality/client-stream-in/disconnected-command.h"

using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

TEST(DisconnectedCommandTest, ToStringTest) {
  DisconnectedCommand command;

  EXPECT_EQ(command.ToString(), "{\"type\":\"Disconnected\"}");
}

TEST(DisconnectedCommandTest, ToJsonTest) {
  DisconnectedCommand command;

  json json_object = {{"type", "Disconnected"}};

  EXPECT_EQ(command.ToJson(), json_object);
}