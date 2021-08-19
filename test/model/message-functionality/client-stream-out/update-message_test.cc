#include "model/message-functionality/client-stream-out/update-message.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

TEST(ClientStreamOutUpdateMessageTest, ToStringTest) {
  UpdateMessage message;

  EXPECT_EQ(message.ToString(), "{\"type\":\"Update\"}");
}

TEST(ClientStreamOutUpdateMessageTest, ToJsonTest) {
  UpdateMessage message;

  json json_object = {{"type", "Update"}};

  EXPECT_EQ(message.ToJson(), json_object);
}