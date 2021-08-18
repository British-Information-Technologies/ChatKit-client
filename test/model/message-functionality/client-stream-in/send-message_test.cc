#include "model/message-functionality/client-stream-in/send-message.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

TEST(SendMessageTest, ToStringTest) {
  SendMessage message;

  EXPECT_EQ(message.ToString(), "{\"type\":\"SendMessage\"}");
}

TEST(SendMessageTest, ToJsonTest) {
  SendMessage message;

  json json_object = {{"type", "SendMessage"}};

  EXPECT_EQ(message.ToJson(), json_object);
}