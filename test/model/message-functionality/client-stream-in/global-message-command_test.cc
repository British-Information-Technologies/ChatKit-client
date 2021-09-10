#include "model/message-functionality/client-stream-in/global-message-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace model_message_functionality_client_stream_in;
using json = nlohmann::json;

TEST(GlobalMessageCommandTest, ToStringTest) {
  std::string content = "hey hey hey";

  GlobalMessageCommand command(content);

  EXPECT_EQ(command.ToString(),
            "{\"content\":\"hey hey hey\",\"type\":\"GlobalMessage\"}");
}

TEST(GlobalMessageCommandTest, ToJsonTest) {
  std::string content = "hey hey hey";

  GlobalMessageCommand command(content);

  json json_object = {{"type", "GlobalMessage"}, {"content", content}};

  EXPECT_EQ(command.ToJson(), json_object);
}