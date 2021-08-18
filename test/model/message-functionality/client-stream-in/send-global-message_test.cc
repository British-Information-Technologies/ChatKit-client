#include "model/message-functionality/client-stream-in/send-global-message.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

TEST(SendGlobalMessageTest, ToStringTest) {
  SendGlobalMessage message;

  EXPECT_EQ(message.ToString(), "{\"type\":\"SendGlobalMessage\"}");
}

TEST(SendGlobalMessageTest, ToJsonTest) {
  SendGlobalMessage message;

  json json_object = {{"type", "SendGlobalMessage"}};

  EXPECT_EQ(message.ToJson(), json_object);
}