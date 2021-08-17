#include "model/message-functionality/message-node.h"

#include <gtest/gtest.h>

#include "model/message-functionality/client-stream-in.h"

using namespace chat_client_model_message_functionality;

TEST(MessageNodeTest, GetContent) {
  std::string content = "This is a message!";

  MessageNode message(content, ClientStreamIn::Connect);

  EXPECT_EQ(message.GetContent(), content);
}

TEST(MessageNodeTest, GetContentDouble) {
  std::string content_one = "one";
  std::string content_two = "two";

  MessageNode message_one(content_one, ClientStreamIn::Connect);
  MessageNode message_two(content_two, ClientStreamIn::Connect);

  EXPECT_EQ(message_one.GetContent(), content_one);
  EXPECT_EQ(message_two.GetContent(), content_two);
}

TEST(MessageNodeTest, GetContentMany) {
  for (int i = 0; i < 250; ++i) {
    std::string content = std::to_string(i);

    MessageNode message(content, ClientStreamIn::Connect);

    EXPECT_EQ(message.GetContent(), content);
  }
}

TEST(MessageNodeTest, GetTypeConnected) {
  std::string content = "one";

  MessageNode message(content, ClientStreamIn::Connect);

  EXPECT_EQ(message.GetType(), ClientStreamIn::Connect);
}

TEST(MessageNodeTest, GetTypeUpdate) {
  std::string content = "one";

  MessageNode message(content, ClientStreamIn::Update);

  EXPECT_EQ(message.GetType(), ClientStreamIn::Update);
}

TEST(MessageNodeTest, GetTypeSendMessage) {
  std::string content = "one";

  MessageNode message(content, ClientStreamIn::SendMessage);

  EXPECT_EQ(message.GetType(), ClientStreamIn::SendMessage);
}

TEST(MessageNodeTest, GetTypeSendGlobalMessage) {
  std::string content = "one";

  MessageNode message(content, ClientStreamIn::SendGlobalMessage);

  EXPECT_EQ(message.GetType(), ClientStreamIn::SendGlobalMessage);
}