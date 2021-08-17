#include "model/message-functionality/message-node.h"

#include <gtest/gtest.h>

using namespace chat_client_model_message_functionality;

TEST(MessageNodeTest, GetContent) {
  std::string content = "This is a message!";

  MessageNode message(content);

  EXPECT_EQ(message.GetContent(), content);
}

TEST(MessageNodeTest, GetContentDouble) {
  std::string content_one = "one";
  std::string content_two = "two";

  MessageNode message_one(content_one);
  MessageNode message_two(content_two);

  EXPECT_EQ(message_one.GetContent(), content_one);
  EXPECT_EQ(message_two.GetContent(), content_two);
}