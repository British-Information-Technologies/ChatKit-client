#include "model/message-functionality/network-stream-out/encrypt-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace model_message_functionality_network_stream_out;
using json = nlohmann::json;

TEST(NetworkStreamOutEncryptCommandTest, ToStringTest) {
  std::string key = "12134";

  EncryptCommand command(key);

  EXPECT_EQ(command.ToString(), "{\"key\":\"12134\",\"type\":\"Encrypt\"}");
}

TEST(NetworkStreamOutEncryptCommandTest, ToJsonTest) {
  std::string key = "12134";

  EncryptCommand command(key);

  json json_object = {{"type", "Encrypt"}, {"key", key}};

  EXPECT_EQ(command.ToJson(), json_object);
}