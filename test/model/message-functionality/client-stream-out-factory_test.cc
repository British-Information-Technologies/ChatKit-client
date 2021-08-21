#include "model/message-functionality/client-stream-out-factory.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality;
using json = nlohmann::json;

TEST(ClientStreamOutFactoryTest, GetDisconnectCommandTest) {
  ClientStreamOutFactory factory;
  std::string type = "Disconnect";

  json json_object = {{"type", type}};

  std::unique_ptr<Message> message = factory.GetMessage(type);

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(ClientStreamOutFactoryTest, GetSendGlobalMessageCommandTest) {
  ClientStreamOutFactory factory;
  std::string type = "SendGlobalMessage";
  std::string content = "very good content ay :]";

  json json_object = {{"type", type}, {"content", content}};

  std::unique_ptr<Message> message = factory.GetMessage(type, content);

  EXPECT_EQ(message->ToString(), json_object.dump());
}

TEST(ClientStreamOutFactoryTest, GetManySendGlobalMessageCommandTest) {
  ClientStreamOutFactory factory;
  std::string type = "SendGlobalMessage";

  for (int i = 0; i < 250; ++i) {
    json json_object = {{"type", type}, {"content", std::to_string(i)}};

    std::unique_ptr<Message> message =
        factory.GetMessage(type, std::to_string(i));

    EXPECT_EQ(message->ToString(), json_object.dump());
  }
}