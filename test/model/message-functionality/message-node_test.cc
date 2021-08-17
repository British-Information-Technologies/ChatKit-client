#include "model/message-functionality/message-node.h"

#include <gtest/gtest.h>

using namespace chat_client_model_message_functionality;

TEST(MessageNodeTest, GetContent) {
  std::string content = "This is a message!";

  MessageNode message;

  EXPECT_EQ(message.GetContent(), content);
}