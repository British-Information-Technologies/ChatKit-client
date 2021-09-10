#include "model/message-functionality/network-stream-out-factory.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace model_message_functionality;
using json = nlohmann::json;

TEST(NetworkStreamOutFactoryTest, GetConnectCommandTest) {
  NetworkStreamOutFactory factory;
  std::string type = "Connect";
  std::string uuid = "1234";
  std::string username = "mitch";
  std::string address = "no address haha!";

  json json_object = {{"type", type},
                      {"uuid", uuid},
                      {"username", username},
                      {"address", address}};
  std::string json_string = json_object.dump();

  std::unique_ptr<Message> message = factory.GetMessage(json_string);

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(NetworkStreamOutFactoryTest, GetManyConnectCommandTest) {
  NetworkStreamOutFactory factory;
  std::string type = "Connect";

  for (int i = 0; i < 250; ++i) {
    json json_object = {{"type", type},
                        {"uuid", std::to_string(i)},
                        {"username", std::to_string(i)},
                        {"address", std::to_string(i)}};
    std::string json_string = json_object.dump();

    std::unique_ptr<Message> message = factory.GetMessage(json_string);

    EXPECT_EQ(message->ToString(), json_object.dump());
  }
}

TEST(NetworkStreamOutFactoryTest, GetInfoCommandTest) {
  NetworkStreamOutFactory factory;
  std::string type = "Info";

  json json_object = {{"type", type}};
  std::string json_string = json_object.dump();

  std::unique_ptr<Message> message = factory.GetMessage(json_string);

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(NetworkStreamOutFactoryTest, GetEncryptCommandTest) {
  NetworkStreamOutFactory factory;
  std::string type = "Encrypt";
  std::string key = "1234";

  json json_object = {{"type", type}, {"key", key}};
  std::string json_string = json_object.dump();

  std::unique_ptr<Message> message = factory.GetMessage(json_string);

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(NetworkStreamOutFactoryTest, GetManyEncryptCommandTest) {
  NetworkStreamOutFactory factory;
  std::string type = "Encrypt";

  for (int i = 0; i < 250; ++i) {
    std::string key = std::to_string(i);

    json json_object = {{"type", type}, {"key", key}};
    std::string json_string = json_object.dump();

    std::unique_ptr<Message> message = factory.GetMessage(json_string);

    EXPECT_EQ(message->ToString(), json_object.dump());
  }
}

TEST(NetworkStreamOutFactoryTest, GetInvalidCommandFromInfoCommandTest) {
  NetworkStreamOutFactory factory;
  json type = {{"type", "Connect"}};
  std::string type_string = type.dump();

  json invalid_object = {{"type", "Invalid"}};

  std::unique_ptr<Message> message = factory.GetMessage(type_string);

  EXPECT_EQ(message->ToString(), invalid_object.dump());
}

TEST(NetworkStreamOutFactoryTest, GetInvalidCommandFromConnectCommandTest) {
  NetworkStreamOutFactory factory;
  std::string type = "Connect";
  std::string uuid = "1234";
  std::string username = "mitch";

  json invalid_object = {{"type", "Invalid"}};

  json command = {{"type", type}, {"uuid", uuid}, {"username", username}};
  std::string command_string = command.dump();

  std::unique_ptr<Message> message = factory.GetMessage(command_string);

  EXPECT_EQ(message->ToString(), invalid_object.dump());
}

TEST(NetworkStreamOutFactoryTest, GetInvalidCommandFromEncryptCommandTest) {
  NetworkStreamOutFactory factory;
  std::string type = "Encrypt";

  json invalid_object = {{"type", "Invalid"}};

  json command = {{"type", type}};
  std::string command_string = command.dump();

  std::unique_ptr<Message> message = factory.GetMessage(command_string);

  EXPECT_EQ(message->ToString(), invalid_object.dump());
}