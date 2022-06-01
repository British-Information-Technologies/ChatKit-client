#include "model/friend-functionality/friend-utility.h"

#include <gtest/gtest.h>

#include <string>

#include "model/friend-functionality/friend-node.h"

using namespace model_friend_functionality;

class FriendUtilityTest : public ::testing::Test {
 public:
  FriendUtilityTest() {
    name_one = "mitch";
    name_two = "micky";

    uuid_one = "test";
    uuid_two = "less";
    
    ip_one = "localhost-one";
    ip_two = "localhost-two"; 

    port_one = "1234";
    port_two = "5678";

    friend_one = new FriendNode(uuid_one, name_one, ip_one, port_one);
    friend_two = new FriendNode(uuid_two, name_two, ip_two, port_two);
  }

 protected:
  std::string name_one;
  std::string name_two;

  std::string uuid_one;
  std::string uuid_two;

  std::string ip_one;
  std::string ip_two;

  std::string port_one;
  std::string port_two;

  FriendNode *friend_one;
  FriendNode *friend_two;
};

TEST_F(FriendUtilityTest, AddFriendTrue) {
  FriendUtility utility;
  EXPECT_TRUE(utility.AddFriend(uuid_one, name_one, ip_one, port_one));
}

TEST_F(FriendUtilityTest, AddFriendDoubleTrue) {
  FriendUtility utility;

  EXPECT_TRUE(utility.AddFriend(uuid_one, name_one, ip_one, port_one));
  EXPECT_TRUE(utility.AddFriend(uuid_two, name_two, ip_two, port_two));
}

TEST_F(FriendUtilityTest, AddFriendFalse) {
  FriendUtility utility;

  EXPECT_TRUE(utility.AddFriend(uuid_one, name_one, ip_one, port_one));
  EXPECT_FALSE(utility.AddFriend(uuid_one, name_one, ip_one, port_one));
}

TEST_F(FriendUtilityTest, AddFriendDoubleFalse) {
  FriendUtility utility;

  EXPECT_TRUE(utility.AddFriend(uuid_one, name_one, ip_one, port_one));
  EXPECT_TRUE(utility.AddFriend(uuid_two, name_two, ip_two, port_two));
  EXPECT_FALSE(utility.AddFriend(uuid_one, name_one, ip_one, port_one));
  EXPECT_FALSE(utility.AddFriend(uuid_two, name_two, ip_two, port_two));
}

TEST_F(FriendUtilityTest, AddFriendManyTrue) {
  FriendUtility utility;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(utility.AddFriend(uuid, name_one, ip_one, port_one));
  }
}

TEST_F(FriendUtilityTest, AddFriendManyFalse) {
  FriendUtility utility;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(utility.AddFriend(uuid, name_one, ip_one, port_one));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_FALSE(utility.AddFriend(uuid, name_one, ip_one, port_one));
  }
}

TEST_F(FriendUtilityTest, GetFriendSingle) {
  FriendUtility utility;

  utility.AddFriend(uuid_one, name_one, ip_one, port_one);
  std::shared_ptr<FriendNode> node_one = utility.GetFriend(uuid_one);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
}

TEST_F(FriendUtilityTest, GetFriendDouble) {
  FriendUtility utility;

  utility.AddFriend(uuid_one, name_one, ip_one, port_one);
  utility.AddFriend(uuid_two, name_two, ip_two, port_two);

  std::shared_ptr<FriendNode> node_one = utility.GetFriend(uuid_one);
  std::shared_ptr<FriendNode> node_two = utility.GetFriend(uuid_two);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
  EXPECT_EQ(node_two->GetUuid(), uuid_two);
}

TEST_F(FriendUtilityTest, GetFriendMany) {
  FriendUtility utility;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(utility.AddFriend(uuid, name_one, ip_one, port_one));
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

  EXPECT_TRUE(utility.AddFriend(uuid_one, name_one, ip_one, port_one));
  EXPECT_TRUE(utility.DeleteFriend(uuid_one));
}

TEST_F(FriendUtilityTest, DeleteFriendDouble) {
  FriendUtility utility;

  EXPECT_TRUE(utility.AddFriend(uuid_one, name_one, ip_one, port_one));
  EXPECT_TRUE(utility.DeleteFriend(uuid_one));

  EXPECT_TRUE(utility.AddFriend(uuid_two, name_two, ip_two, port_two));
  EXPECT_TRUE(utility.DeleteFriend(uuid_two));
}

TEST_F(FriendUtilityTest, DeleteFriendMany) {
  FriendUtility utility;

  for (int i = 0; i < 100; ++i) {
    EXPECT_TRUE(utility.AddFriend(uuid_one, name_one, ip_one, port_one));
    EXPECT_TRUE(utility.DeleteFriend(uuid_one));
  }
}

TEST_F(FriendUtilityTest, DeleteFriendError) {
  FriendUtility utility;

  EXPECT_FALSE(utility.DeleteFriend(uuid_one));
}

TEST_F(FriendUtilityTest, AddDeleteDeleteFriendError) {
  FriendUtility utility;

  EXPECT_TRUE(utility.AddFriend(uuid_one, name_one, ip_one, port_one));
  EXPECT_TRUE(utility.DeleteFriend(uuid_one));
  EXPECT_FALSE(utility.DeleteFriend(uuid_one));
}

TEST_F(FriendUtilityTest, Begin) {
  FriendUtility utility;

  auto begin = utility.Begin();

  SUCCEED();
}

TEST_F(FriendUtilityTest, End) {
  FriendUtility utility;

  auto begin = utility.End();

  SUCCEED();
}