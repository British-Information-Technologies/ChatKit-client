#include "model/message-functionality/client-stream-out/disconnect-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace model_message_functionality_client_stream_out;
using json = nlohmann::json;

TEST(DisconnectCommandTest, ToStringTest) {
  DisconnectCommand command;

  EXPECT_EQ(command.ToString(), "{\"type\":\"Disconnect\"}");
}

TEST(DisconnectCommandTest, ToJsonTest) {
  DisconnectCommand command;

  json json_object = {{"type", "Disconnect"}};

  EXPECT_EQ(command.ToJson(), json_object);
}