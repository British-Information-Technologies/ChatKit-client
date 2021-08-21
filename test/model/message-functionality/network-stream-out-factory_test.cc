#include "model/message-functionality/network-stream-out-factory.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using namespace chat_client_model_message_functionality;
using json = nlohmann::json;

TEST(NetworkStreamOutFactoryTest, GetConnectCommandTest) {
  NetworkStreamOutFactory factory;

  json json_object = {{"type", "Connect"},
                      {"uuid", "1234"},
                      {"username", "mitch"},
                      {"address", "no address haha!"}};

  std::unique_ptr<Message> message = factory.GetMessage();

  EXPECT_EQ(message->ToString(), json_object.dump());
}