#include "model/message-functionality/client-stream-in/connect-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace model_message_functionality_client_stream_in;
using json = nlohmann::json;

TEST(ConnectCommandTest, ToStringTest) {
  ConnectCommand command;

  EXPECT_EQ(command.ToString(), "{\"type\":\"Connect\"}");
}

TEST(ConnectCommandTest, ToJsonTest) {
  ConnectCommand command;

  json json_object = {{"type", "Connect"}};

  EXPECT_EQ(command.ToJson(), json_object);
}