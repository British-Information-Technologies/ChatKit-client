#include "model/message-functionality/network-stream-in/key-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace model_message_functionality_network_stream_in;
using json = nlohmann::json;

TEST(KeyCommandTest, ToStringTest) {
  std::string key = "1234";

  KeyCommand command(key);

  EXPECT_EQ(command.ToString(), "{\"key\":\"1234\",\"type\":\"Key\"}");
}

TEST(KeyCommandTest, ToJsonTest) {
  std::string key = "1234";

  KeyCommand command(key);

  json json_object = {{"type", "Key"}, {"key", key}};

  EXPECT_EQ(command.ToJson(), json_object);
}