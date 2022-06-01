#include "model/message-functionality/client-stream-out-factory.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace model_message_functionality;
using json = nlohmann::json;

TEST(ClientStreamOutFactoryTest, GetDisconnectCommandTest) {
  ClientStreamOutFactory factory;
  std::string type = "Disconnect";

  json json_object = {{"type", type}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(ClientStreamOutFactoryTest, GetSendGlobalMessageCommandTest) {
  ClientStreamOutFactory factory;
  std::string type = "SendGlobalMessage";
  std::string content = "very good content ay :]";

  json json_object = {{"type", type}, {"content", content}};
  std::string json_string = json_object.dump();

  std::unique_ptr<Message> message = factory.GetMessage(json_string);

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(ClientStreamOutFactoryTest, GetManySendGlobalMessageCommandTest) {
  ClientStreamOutFactory factory;
  std::string type = "SendGlobalMessage";

  for (int i = 0; i < 250; ++i) {
    json json_object = {{"type", type}, {"content", std::to_string(i)}};
    std::string json_string = json_object.dump();

    std::unique_ptr<Message> message = factory.GetMessage(json_string);

    EXPECT_EQ(message->ToString(), json_object.dump());
  }
}

TEST(ClientStreamOutFactoryTest, GetSendMessageCommandTest) {
  ClientStreamOutFactory factory;
  std::string type = "SendMessage";
  std::string to = "mitch";
  std::string content = "hey!";

  json json_object = {{"type", type}, {"to", to}, {"content", content}};
  std::string json_string = json_object.dump();

  std::unique_ptr<Message> message = factory.GetMessage(json_string);

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(ClientStreamOutFactoryTest, GetManySendMessageCommandTest) {
  ClientStreamOutFactory factory;
  std::string type = "SendMessage";

  for (int i = 0; i < 250; ++i) {
    json json_object = {{"type", type},
                        {"to", std::to_string(i)},
                        {"content", std::to_string(i)}};
    std::string json_string = json_object.dump();

    std::unique_ptr<Message> message = factory.GetMessage(json_string);

    EXPECT_EQ(message->ToString(), json_object.dump());
  }
}

TEST(ClientStreamOutFactoryTest, GetUpdateCommandTest) {
  ClientStreamOutFactory factory;
  std::string type = "Update";

  json json_object = {{"type", type}};

  std::unique_ptr<Message> message = factory.GetMessage(json_object.dump());

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(NetworkStreamOutFactoryTest, GetInvalidCommandFromDisconnectCommandTest) {
  ClientStreamOutFactory factory;
  std::string type = "SendGlobalMessageCommand";

  json invalid_object = {{"type", "Invalid"}};

  std::unique_ptr<Message> message = factory.GetMessage(type);

  EXPECT_EQ(message->ToString(), invalid_object.dump());
}

TEST(NetworkStreamOutFactoryTest,
     GetInvalidCommandFromSendGlobalMessageCommandTest) {
  ClientStreamOutFactory factory;
  std::string type = "SendMessageCommand";
  std::string content = "this is so meeeeee!";

  json invalid_object = {{"type", "Invalid"}};
  std::string json_string = invalid_object.dump();

  std::unique_ptr<Message> message = factory.GetMessage(json_string);

  EXPECT_EQ(message->ToString(), invalid_object.dump());
}

TEST(NetworkStreamOutFactoryTest, GetInvalidCommandFromSendMessageCommandTest) {
  ClientStreamOutFactory factory;
  std::string type = "SendMessageCommand";
  std::string to = "mitch";
  std::string content = "this is so meeeeee!";

  json invalid_object = {{"type", "Invalid"}};
  std::string json_string = invalid_object.dump();

  std::unique_ptr<Message> message = factory.GetMessage(json_string);

  EXPECT_EQ(message->ToString(), invalid_object.dump());
}