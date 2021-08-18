#include "model/message-functionality/client-stream-in/connected-message.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

TEST(ConnectedMessageTest, ToStringTest) {
  ConnectedMessage message;

  EXPECT_EQ(message.ToString(), "{\"type\":\"connect\"}");
}

TEST(ConnectedMessageTest, ToJsonTest) {
  ConnectedMessage message;

  json json_object = {{"type", "connect"}};

  EXPECT_EQ(message.ToJson(), json_object);
}