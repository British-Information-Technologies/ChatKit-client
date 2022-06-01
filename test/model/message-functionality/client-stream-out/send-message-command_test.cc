#include "model/message-functionality/client-stream-out/send-message-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace model_message_functionality_client_stream_out;
using json = nlohmann::json;

TEST(SendMessageCommandTest, ToStringTest) {
  std::string to = "mitch";
  std::string content = "hey hey hey";

  SendMessageCommand command(to, content);

  EXPECT_EQ(command.ToString(),
            "{\"content\":\"hey hey "
            "hey\",\"to\":\"mitch\",\"type\":\"SendMessage\"}");
}

TEST(SendMessageCommandTest, ToJsonTest) {
  std::string to = "mitch";
  std::string content = "hey hey hey";

  SendMessageCommand command(to, content);

  json json_object = {
      {"type", "SendMessage"}, {"to", to}, {"content", content}};

  EXPECT_EQ(command.ToJson(), json_object);
}