#include "model/message-functionality/general/invalid-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_general;
using json = nlohmann::json;

TEST(InvalidCommandTest, ToStringTest) {
  InvalidCommand command;

  EXPECT_EQ(command.ToString(), "{\"type\":\"Invalid\"}");
}

TEST(InvalidCommandTest, ToJsonTest) {
  InvalidCommand command;

  json json_object = {{"type", "Invalid"}};

  EXPECT_EQ(command.ToJson(), json_object);
}