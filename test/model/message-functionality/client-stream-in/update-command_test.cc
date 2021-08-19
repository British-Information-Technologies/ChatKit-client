#include "model/message-functionality/client-stream-in/update-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

TEST(ClientStreamOutUpdateCommandTest, ToStringTest) {
  UpdateCommand command;

  EXPECT_EQ(command.ToString(), "{\"type\":\"Update\"}");
}

TEST(ClientStreamOutUpdateCommandTest, ToJsonTest) {
  UpdateCommand command;

  json json_object = {{"type", "Update"}};

  EXPECT_EQ(command.ToJson(), json_object);
}