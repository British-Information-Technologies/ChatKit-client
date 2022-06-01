#include "model/message-functionality/network-stream-in/request-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace model_message_functionality_network_stream_in;
using json = nlohmann::json;

TEST(RequestCommandTest, ToStringTest) {
  RequestCommand command;

  EXPECT_EQ(command.ToString(), "{\"type\":\"Request\"}");
}

TEST(RequestCommandTest, ToJsonTest) {
  RequestCommand command;

  json json_object = {{"type", "Request"}};

  EXPECT_EQ(command.ToJson(), json_object);
}