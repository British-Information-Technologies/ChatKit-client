#include "model/message-functionality/client-stream-out/connect-message.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

TEST(ConnectMessageTest, ToStringTest) {
  ConnectMessage message;

  EXPECT_EQ(message.ToString(), "{\"type\":\"Connect\"}");
}

TEST(ConnectMessageTest, ToJsonTest) {
  ConnectMessage message;

  json json_object = {{"type", "Connect"}};

  EXPECT_EQ(message.ToJson(), json_object);
}