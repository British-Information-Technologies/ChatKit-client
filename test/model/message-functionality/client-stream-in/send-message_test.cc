#include "model/message-functionality/client-stream-in/send-message.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

TEST(SendMessageTest, ToStringTest) {
  std::string to = "mitch";
  std::string content = "hey hey hey";

  SendMessage message(to, content);

  EXPECT_EQ(message.ToString(),
            "{\"content\":\"hey hey "
            "hey\",\"to\":\"mitch\",\"type\":\"SendMessage\"}");
}

TEST(SendMessageTest, ToJsonTest) {
  std::string to = "mitch";
  std::string content = "hey hey hey";

  SendMessage message(to, content);

  json json_object = {
      {"type", "SendMessage"}, {"to", to}, {"content", content}};

  EXPECT_EQ(message.ToJson(), json_object);
}