#include "model/message-functionality/network-stream-in/got-info-command.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality_network_stream_in;
using json = nlohmann::json;

TEST(GotInfoCommandTest, ToStringTest) {
  std::string server_name = "test server";
  std::string server_owner = "mitch";

  GotInfoCommand command(server_name, server_owner);

  EXPECT_EQ(command.ToString(),
            "{\"server name\":\"test server\",\"server "
            "owner\":\"mitch\",\"type\":\"GotInfo\"}");
}

TEST(GotInfoCommandTest, ToJsonTest) {
  std::string server_name = "test server";
  std::string server_owner = "mitch";

  GotInfoCommand command(server_name, server_owner);

  json json_object = {{"type", "GotInfo"},
                      {"server name", server_name},
                      {"server owner", server_owner}};

  EXPECT_EQ(command.ToJson(), json_object);
}