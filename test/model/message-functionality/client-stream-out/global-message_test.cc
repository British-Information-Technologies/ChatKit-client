#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include "model/message-functionality/client-stream-out/global-message.h"

using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

TEST(GlobalMessageTest, ToStringTest) {
  std::string content = "hey hey hey";

  GlobalMessage message(content);

  EXPECT_EQ(message.ToString(),
            "{\"content\":\"hey hey hey\",\"type\":\"GlobalMessage\"}");
}

TEST(GlobalMessageTest, ToJsonTest) {
  std::string content = "hey hey hey";

  GlobalMessage message(content);

  json json_object = {{"type", "GlobalMessage"}, {"content", content}};

  EXPECT_EQ(message.ToJson(), json_object);
}