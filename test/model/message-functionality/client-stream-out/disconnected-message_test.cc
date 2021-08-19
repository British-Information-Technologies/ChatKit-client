#include "model/message-functionality/client-stream-out/disconnected-message.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

TEST(DisconnectedMessageTest, ToStringTest) {
  DisconnectedMessage message;

  EXPECT_EQ(message.ToString(), "{\"type\":\"Disconnected\"}");
}

TEST(DisconnectedMessageTest, ToJsonTest) {
  DisconnectedMessage message;

  json json_object = {{"type", "Disconnected"}};

  EXPECT_EQ(message.ToJson(), json_object);
}