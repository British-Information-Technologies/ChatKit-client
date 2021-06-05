#include "model/friend-functionality/friend-utility.h"

#include <gtest/gtest.h>

#include <string>

#include "model/friend-functionality/friend-node.h"

using namespace chat_client_model_friend_functionality;

class FriendUtilityTest : public ::testing::Test {};

TEST_F(FriendUtilityTest, AddFriendTrue) {
  FriendUtility utility;
  std::string name = "mitch";
  std::string uuid_one = "test";
  FriendNode *friend_one = new FriendNode(&name, &uuid_one);

  EXPECT_TRUE(utility.AddFriend(*friend_one));
}