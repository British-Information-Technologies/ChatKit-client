#include "model/message-functionality/client-stream-out/send-global-message-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace model_message_functionality_client_stream_out;
using json = nlohmann::json;

TEST(SendGlobalMessageCommandTest, ToStringTest) {
  std::string content = "hey hey hey";

  SendGlobalMessageCommand command(content);

  EXPECT_EQ(command.ToString(),
            "{\"content\":\"hey hey hey\",\"type\":\"SendGlobalMessage\"}");
}

TEST(SendGlobalMessageCommandTest, ToJsonTest) {
  std::string content = "hey hey hey";

  SendGlobalMessageCommand command(content);

  json json_object = {{"type", "SendGlobalMessage"}, {"content", content}};

  EXPECT_EQ(command.ToJson(), json_object);
}