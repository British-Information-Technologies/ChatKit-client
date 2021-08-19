#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include "model/message-functionality/client-stream-in/error-command.h"

using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

TEST(ErrorCommandTest, ToStringTest) {
  ErrorCommand command;

  EXPECT_EQ(command.ToString(), "{\"type\":\"Error\"}");
}

TEST(ErrorCommandTest, ToJsonTest) {
  ErrorCommand command;

  json json_object = {{"type", "Error"}};

  EXPECT_EQ(command.ToJson(), json_object);
}