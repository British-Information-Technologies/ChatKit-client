#include "model/message-functionality/client-stream-in/update-message.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

TEST(UpdateMessageTest, ToStringTest) {
  UpdateMessage message;

  EXPECT_EQ(message.ToString(), "{\"type\":\"update\"}");
}

TEST(UpdateMessageTest, ToJsonTest) {
  UpdateMessage message;

  json json_object = {{"type", "update"}};

  EXPECT_EQ(message.ToJson(), json_object);
}