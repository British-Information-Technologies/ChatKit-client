#include "model/message-functionality/client-stream-out/error-message.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

TEST(ErrorMessageTest, ToStringTest) {
  ErrorMessage message;

  EXPECT_EQ(message.ToString(), "{\"type\":\"Error\"}");
}

TEST(ErrorMessageTest, ToJsonTest) {
  ErrorMessage message;

  json json_object = {{"type", "Error"}};

  EXPECT_EQ(message.ToJson(), json_object);
}