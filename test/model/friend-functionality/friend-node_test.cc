#include "model/friend-functionality/friend-node.h"

#include <gtest/gtest.h>

#include <string>

using namespace chat_client_model_friend_functionality;

class FriendNodeTest : public ::testing::Test {
 public:
  FriendNodeTest() {
    std::string name_one = "mitch";
    std::string name_two = "micky";
    friend_one = new FriendNode(&name_one);
    friend_two = new FriendNode(&name_two);
  }

 protected:
  FriendNode *friend_one;
  FriendNode *friend_two;
};

TEST_F(FriendNodeTest, GetName) {
  std::string name = "mitch";
  EXPECT_EQ(friend_one->GetName(), name);
}

TEST_F(FriendNodeTest, GetNameDouble) {
  std::string name_one = "mitch";
  std::string name_two = "micky";

  EXPECT_EQ(friend_one->GetName(), name_one);
  EXPECT_EQ(friend_two->GetName(), name_two);
}

TEST_F(FriendNodeTest, GetNameConstant) {
  std::string name = "mitch";
  FriendNode tmp_friend(&name);

  EXPECT_EQ(tmp_friend.GetName(), name);

  name = "bob";
  EXPECT_NE(tmp_friend.GetName(), name);

  name = "mitch";
  EXPECT_EQ(tmp_friend.GetName(), name);
}