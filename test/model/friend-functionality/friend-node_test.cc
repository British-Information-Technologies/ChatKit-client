#include "model/friend-functionality/friend-node.h"

#include <gtest/gtest.h>

#include <string>

using namespace chat_client_model_friend_functionality;

class FriendNodeTest : public ::testing::Test {
 protected:
  FriendNode friend_one;
};

TEST_F(FriendNodeTest, GetName) {
  std::string name = "mitch";
  EXPECT_EQ(friend_one.GetName(), name);
}