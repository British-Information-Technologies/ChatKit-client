#include "model/message-functionality/network-stream-out-factory.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality;
using json = nlohmann::json;

TEST(NetworkStreamOutFactoryTest, GetConnectCommandTest) {
  NetworkStreamOutFactory factory;
  std::string uuid = "1234";
  std::string username = "mitch";
  std::string address = "no address haha!";

  json json_object = {{"type", "Connect"},
                      {"uuid", uuid},
                      {"username", username},
                      {"address", address}};

  std::unique_ptr<Message> message =
      factory.GetMessage(uuid, username, address);

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(NetworkStreamOutFactoryTest, GetManyConnectCommandTest) {
  NetworkStreamOutFactory factory;

  for (int i = 0; i < 250; ++i) {
    json json_object = {{"type", "Connect"},
                        {"uuid", std::to_string(i)},
                        {"username", std::to_string(i)},
                        {"address", std::to_string(i)}};

    std::unique_ptr<Message> message = factory.GetMessage(
        std::to_string(i), std::to_string(i), std::to_string(i));

    EXPECT_EQ(message->ToString(), json_object.dump());
  }
}