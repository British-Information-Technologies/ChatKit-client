#include "model/message-functionality/network-stream-out/info-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_network_stream_out;
using json = nlohmann::json;

TEST(InfoCommandTest, ToStringTest) {
  InfoCommand command;

  EXPECT_EQ(command.ToString(), "{\"type\":\"Info\"}");
}

TEST(InfoCommandTest, ToJsonTest) {
  InfoCommand command;

  json json_object = {{"type", "Info"}};

  EXPECT_EQ(command.ToJson(), json_object);
}