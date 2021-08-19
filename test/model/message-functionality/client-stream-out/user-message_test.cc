#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include "model/message-functionality/client-stream-out/user-message.h"

using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

TEST(UserMessageTest, ToStringTest) {
  std::string from = "mitch";
  std::string content = "hey hey hey";

  UserMessage message(from, content);

  EXPECT_EQ(message.ToString(),
            "{\"content\":\"hey hey "
            "hey\",\"from\":\"mitch\",\"type\":\"UserMessage\"}");
}

TEST(UserMessageTest, ToJsonTest) {
  std::string from = "mitch";
  std::string content = "hey hey hey";

  UserMessage message(from, content);

  json json_object = {
      {"type", "UserMessage"}, {"from", from}, {"content", content}};

  EXPECT_EQ(message.ToJson(), json_object);
}