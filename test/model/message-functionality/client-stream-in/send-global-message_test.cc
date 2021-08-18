#include "model/message-functionality/client-stream-in/send-global-message.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

TEST(SendGlobalMessageTest, ToStringTest) {
  std::string content = "hey hey hey";

  SendGlobalMessage message(content);

  EXPECT_EQ(message.ToString(),
            "{\"content\":\"hey hey hey\",\"type\":\"SendGlobalMessage\"}");
}

TEST(SendGlobalMessageTest, ToJsonTest) {
  std::string content = "hey hey hey";

  SendGlobalMessage message(content);

  json json_object = {{"type", "SendGlobalMessage"}, {"content", content}};

  EXPECT_EQ(message.ToJson(), json_object);
}