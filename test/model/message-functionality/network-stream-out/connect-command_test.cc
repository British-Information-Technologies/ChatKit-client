#include "model/message-functionality/network-stream-out/connect-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_network_stream_out;
using json = nlohmann::json;

TEST(NetworkStreamOutConnectCommandTest, ToStringTest) {
  std::string uuid = "12134";
  std::string username = "mitch";
  std::string address = "hahahah";

  ConnectCommand command(uuid, username, address);

  EXPECT_EQ(command.ToString(),
            "{\"address\":\"hahahah\",\"type\":\"Connect\",\"username\":"
            "\"mitch\",\"uuid\":\"12134\"}");
}

TEST(NetworkStreamOutConnectCommandTest, ToJsonTest) {
  std::string uuid = "12134";
  std::string username = "mitch";
  std::string address = "hahahah";

  ConnectCommand command(uuid, username, address);

  json json_object = {{"type", "Connect"},
                      {"uuid", uuid},
                      {"username", username},
                      {"address", address}};

  EXPECT_EQ(command.ToJson(), json_object);
}