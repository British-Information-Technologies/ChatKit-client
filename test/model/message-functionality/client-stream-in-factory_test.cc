#include "model/message-functionality/client-stream-in-factory.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality;
using json = nlohmann::json;

TEST(ClientStreamInFactoryTest, GetConnectCommandTest) {
  ClientStreamInFactory factory;

  json json_object = {{"type", "Connect"}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(ClientStreamInFactoryTest, GetDisconnectedCommandTest) {
  ClientStreamInFactory factory;

  json json_object = {{"type", "Disconnected"}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(ClientStreamInFactoryTest, GetErrorCommandTest) {
  ClientStreamInFactory factory;

  json json_object = {{"type", "Error"}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(ClientStreamInFactoryTest, GetGlobalMessageCommandTest) {
  ClientStreamInFactory factory;

  json json_object = {{"type", "GlobalMessage"},
                      {"content", "this is a message!"}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(ClientStreamInFactoryTest, GetManyGlobalMessageCommandTest) {
  ClientStreamInFactory factory;

  for (int i = 0; i < 250; ++i) {
    json json_object = {{"type", "GlobalMessage"},
                        {"content", std::to_string(i)}};

    std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

    EXPECT_EQ(message->ToString(), json_object.dump());
  }
}

TEST(ClientStreamInFactoryTest, GetUpdateCommandTest) {
  ClientStreamInFactory factory;

  json json_object = {{"type", "Update"}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(ClientStreamInFactoryTest, GetUserMessageCommandTest) {
  ClientStreamInFactory factory;

  json json_object = {
      {"type", "UserMessage"}, {"content", "hey hey hey!"}, {"from", "mitch"}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(ClientStreamInFactoryTest, GetManyUserMessageCommandTest) {
  ClientStreamInFactory factory;

  for (int i = 0; i < 250; ++i) {
    json json_object = {{"type", "UserMessage"},
                        {"content", std::to_string(i)},
                        {"from", std::to_string(i)}};

    std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

    EXPECT_EQ(message->ToString(), json_object.dump());
  }
}