#include "model/message-functionality/network-stream-in-factory.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality;
using json = nlohmann::json;

TEST(NetworkStreamInFactoryTest, GetConnectingCommandTest) {
  NetworkStreamInFactory factory;

  json json_object = {{"type", "Connecting"}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(NetworkStreamInFactoryTest, GetGotInfoCommandTest) {
  NetworkStreamInFactory factory;

  json json_object = {{"type", "GotInfo"},
                      {"server owner", "mitch"},
                      {"server name", "test server"}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(NetworkStreamInFactoryTest, GetManyGotInfoCommandTest) {
  NetworkStreamInFactory factory;

  for (int i = 0; i < 250; ++i) {
    json json_object = {{"type", "GotInfo"},
                        {"server owner", std::to_string(i)},
                        {"server name", std::to_string(i)}};

    std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

    EXPECT_EQ(message->ToString(), json_object.dump());
  }
}

TEST(NetworkStreamInFactoryTest, GetRequestCommandTest) {
  NetworkStreamInFactory factory;

  json json_object = {{"type", "Request"}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), json_object.dump());
}