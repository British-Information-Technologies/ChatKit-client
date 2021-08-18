#include "model/message-functionality/client-stream-in/disconnect-message.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

TEST(DisconnectMessageTest, ToStringTest) {
  DisconnectMessage message;

  EXPECT_EQ(message.ToString(), "{\"type\":\"Disconnect\"}");
}

TEST(DisconnectMessageTest, ToJsonTest) {
  DisconnectMessage message;

  json json_object = {{"type", "Disconnect"}};

  EXPECT_EQ(message.ToJson(), json_object);
}