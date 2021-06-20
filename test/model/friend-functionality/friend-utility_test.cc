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
    friend_one = new FriendNode(name, uuid_one);
    friend_two = new FriendNode(name, uuid_two);
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
  EXPECT_TRUE(utility.AddFriend(uuid_one));
}

TEST_F(FriendUtilityTest, AddFriendDoubleTrue) {
  FriendUtility utility;

  EXPECT_TRUE(utility.AddFriend(uuid_one));
  EXPECT_TRUE(utility.AddFriend(uuid_two));
}

TEST_F(FriendUtilityTest, AddFriendFalse) {
  FriendUtility utility;

  EXPECT_TRUE(utility.AddFriend(uuid_one));
  EXPECT_FALSE(utility.AddFriend(uuid_one));
}

TEST_F(FriendUtilityTest, AddFriendDoubleFalse) {
  FriendUtility utility;

  EXPECT_TRUE(utility.AddFriend(uuid_one));
  EXPECT_TRUE(utility.AddFriend(uuid_two));
  EXPECT_FALSE(utility.AddFriend(uuid_one));
  EXPECT_FALSE(utility.AddFriend(uuid_two));
}

TEST_F(FriendUtilityTest, AddFriendManyTrue) {
  FriendUtility utility;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(utility.AddFriend(uuid));
  }
}

TEST_F(FriendUtilityTest, AddFriendManyFalse) {
  FriendUtility utility;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(utility.AddFriend(uuid));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_FALSE(utility.AddFriend(uuid));
  }
}

TEST_F(FriendUtilityTest, GetFriendSingle) {
  FriendUtility utility;

  utility.AddFriend(uuid_one);
  std::shared_ptr<FriendNode> node_one = utility.GetFriend(uuid_one);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
}

TEST_F(FriendUtilityTest, GetFriendDouble) {
  FriendUtility utility;

  utility.AddFriend(uuid_one);
  utility.AddFriend(uuid_two);

  std::shared_ptr<FriendNode> node_one = utility.GetFriend(uuid_one);
  std::shared_ptr<FriendNode> node_two = utility.GetFriend(uuid_two);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
  EXPECT_EQ(node_two->GetUuid(), uuid_two);
}

TEST_F(FriendUtilityTest, GetFriendMany) {
  FriendUtility utility;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(utility.AddFriend(uuid));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_EQ(utility.GetFriend(uuid)->GetUuid(), uuid);
  }
}

TEST_F(FriendUtilityTest, GetFriendError) {
  FriendUtility utility;

  try {
    utility.GetFriend(uuid_one);
    FAIL();
  } catch (const std::out_of_range &err) {
    EXPECT_STREQ("map::at", err.what());
  }
}

TEST_F(FriendUtilityTest, DeleteFriendSingle) {
  FriendUtility utility;

  EXPECT_TRUE(utility.AddFriend(uuid_one));
  EXPECT_TRUE(utility.DeleteFriend(uuid_one));
}