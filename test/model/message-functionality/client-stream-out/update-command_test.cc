#include "model/message-functionality/client-stream-out/update-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace model_message_functionality_client_stream_out;
using json = nlohmann::json;

TEST(UpdateCommandTest, ToStringTest) {
  UpdateCommand command;

  EXPECT_EQ(command.ToString(), "{\"type\":\"Update\"}");
}

TEST(UpdateCommandTest, ToJsonTest) {
  UpdateCommand command;

  json json_object = {{"type", "Update"}};

  EXPECT_EQ(command.ToJson(), json_object);
}