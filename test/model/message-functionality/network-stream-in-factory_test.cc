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

TEST(NetworkStreamInFactoryTest, GetKeyCommandTest) {
  NetworkStreamInFactory factory;

  std::string key = "1234";

  json json_object = {{"type", "Key"}, {"key", key}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(NetworkStreamInFactoryTest, GetManyKeyCommandTest) {
  NetworkStreamInFactory factory;

  for (int i = 0; i < 250; ++i) {
    std::string key = std::to_string(i);

    json json_object = {{"type", "Key"}, {"key", key}};

    std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

    EXPECT_EQ(message->ToString(), json_object.dump());
  }
}

TEST(NetworkStreamInFactoryTest, GetInvalidCommandTest) {
  NetworkStreamInFactory factory;

  json json_object = {{"type", "Connect"}};
  json invalid_object = {{"type", "Invalid"}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), invalid_object.dump());
}

TEST(NetworkStreamInFactoryTest, GetInvalidGotInfoCommandNoNameTest) {
  NetworkStreamInFactory factory;

  json json_object = {{"type", "GotInfo"}, {"server owner", "mitch"}};
  json invalid_object = {{"type", "Invalid"}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), invalid_object.dump());
}

TEST(NetworkStreamInFactoryTest, GetInvalidGotInfoCommandNoOwnerTest) {
  NetworkStreamInFactory factory;
  json json_object = {{"type", "GotInfo"}, {"server name", "mitch"}};
  json invalid_object = {{"type", "Invalid"}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), invalid_object.dump());
}

TEST(NetworkStreamInFactoryTest, GetInvalidCommandNoTypeTest) {
  NetworkStreamInFactory factory;

  json json_object = {{"content", "hahaha"}};
  json invalid_object = {{"type", "Invalid"}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), invalid_object.dump());
}