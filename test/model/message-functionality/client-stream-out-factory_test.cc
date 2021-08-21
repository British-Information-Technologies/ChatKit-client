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

  json json_object = {{"type", type}, {"content", "very good content ay :]"}};

  std::unique_ptr<Message> message = factory.GetMessage(type);

  EXPECT_EQ(message->ToString(), json_object.dump());
}