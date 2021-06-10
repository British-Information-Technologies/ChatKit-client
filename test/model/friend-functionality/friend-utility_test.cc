#include "model/friend-functionality/friend-utility.h"

#include <gtest/gtest.h>

#include <string>

#include "model/friend-functionality/friend-node.h"

using namespace chat_client_model_friend_functionality;

class FriendUtilityTest : public ::testing::Test {
 public:
  FriendUtilityTest() {
    name = "mitch";
    uuid_one = "test";
    uuid_two = "less";
    friend_one = new FriendNode(&name, &uuid_one);
    friend_two = new FriendNode(&name, &uuid_two);
  }

 protected:
  std::string name;
  std::string uuid_one;
  std::string uuid_two;
  FriendNode *friend_one;
  FriendNode *friend_two;
};

TEST_F(FriendUtilityTest, AddFriendTrue) {
  FriendUtility utility;
  EXPECT_TRUE(utility.AddFriend(*friend_one));
}

TEST_F(FriendUtilityTest, AddFriendDoubleTrue) {
  FriendUtility utility;

  EXPECT_TRUE(utility.AddFriend(*friend_one));
  EXPECT_TRUE(utility.AddFriend(*friend_two));
}

TEST_F(FriendUtilityTest, AddFriendFalse) {
  FriendNode friend_tmp(&name, &uuid_one);
  FriendUtility utility;

  EXPECT_TRUE(utility.AddFriend(*friend_one));
  EXPECT_FALSE(utility.AddFriend(friend_tmp));
}

TEST_F(FriendUtilityTest, AddFriendDoubleFalse) {
  FriendUtility utility;

  EXPECT_TRUE(utility.AddFriend(*friend_one));
  EXPECT_TRUE(utility.AddFriend(*friend_two));
  EXPECT_FALSE(utility.AddFriend(*friend_one));
  EXPECT_FALSE(utility.AddFriend(*friend_two));
}

TEST_F(FriendUtilityTest, AddFriendManyTrue) {
  FriendUtility utility;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    FriendNode friend_node(&name, &uuid);
    EXPECT_TRUE(utility.AddFriend(friend_node));
  }
}

TEST_F(FriendUtilityTest, AddFriendManyFalse) {
  FriendUtility utility;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    FriendNode friend_node(&name, &uuid);
    EXPECT_TRUE(utility.AddFriend(friend_node));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    FriendNode friend_node(&name, &uuid);
    EXPECT_FALSE(utility.AddFriend(friend_node));
  }
}