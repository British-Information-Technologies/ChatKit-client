#include "model/message-functionality/client-stream-out-factory.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality;
using json = nlohmann::json;

TEST(ClientStreamOutFactoryTest, GetDisconnectCommandTest) {
  ClientStreamOutFactory factory;

  json json_object = {{"type", "Disconnect"}};

  std::unique_ptr<Message> message = factory.GetMessage();

  EXPECT_EQ(message->ToString(), json_object.dump());
}