#include "model/message-functionality/client-stream-in/user-message-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

TEST(UserMessageCommandTest, ToStringTest) {
  std::string from = "mitch";
  std::string content = "hey hey hey";

  UserMessageCommand command(from, content);

  EXPECT_EQ(command.ToString(),
            "{\"content\":\"hey hey "
            "hey\",\"from\":\"mitch\",\"type\":\"UserMessage\"}");
}

TEST(UserMessageCommandTest, ToJsonTest) {
  std::string from = "mitch";
  std::string content = "hey hey hey";

  UserMessageCommand command(from, content);

  json json_object = {
      {"type", "UserMessage"}, {"from", from}, {"content", content}};

  EXPECT_EQ(command.ToJson(), json_object);
}