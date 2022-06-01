#include "model/friend-functionality/friend-hashmap.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <stdexcept>

#include "model/friend-functionality/friend-node.h"

using namespace model_friend_functionality;

class FriendHashmapTest : public ::testing::Test {
 public:
  FriendHashmapTest() {
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

TEST_F(FriendHashmapTest, AddFriendTrue) {
  FriendHashmap friend_list;

  EXPECT_TRUE(friend_list.AddFriend(*friend_one));
}
 
TEST_F(FriendHashmapTest, AddFriendDoubleTrue) {
  FriendHashmap friend_list;

  EXPECT_TRUE(friend_list.AddFriend(*friend_one));
  EXPECT_TRUE(friend_list.AddFriend(*friend_two));
}

TEST_F(FriendHashmapTest, AddFriendFalse) {
  FriendNode friend_tmp(uuid_one, name_one, ip_one, port_one);
  FriendHashmap friend_list;

  EXPECT_TRUE(friend_list.AddFriend(*friend_one));
  EXPECT_FALSE(friend_list.AddFriend(friend_tmp));
}

TEST_F(FriendHashmapTest, AddFriendDoubleFalse) {
  FriendHashmap friend_list;

  EXPECT_TRUE(friend_list.AddFriend(*friend_one));
  EXPECT_TRUE(friend_list.AddFriend(*friend_two));
  EXPECT_FALSE(friend_list.AddFriend(*friend_one));
  EXPECT_FALSE(friend_list.AddFriend(*friend_two));
}

TEST_F(FriendHashmapTest, AddFriendManyTrue) {
  FriendHashmap friend_list;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    FriendNode friend_node(uuid, name_one, ip_one, port_one);
    EXPECT_TRUE(friend_list.AddFriend(friend_node));
  }
}

TEST_F(FriendHashmapTest, AddFriendManyFalse) {
  FriendHashmap friend_list;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    FriendNode friend_node(uuid, name_one, ip_one, port_one);
    EXPECT_TRUE(friend_list.AddFriend(friend_node));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    FriendNode friend_node(uuid, name_one, ip_one, port_one);
    EXPECT_FALSE(friend_list.AddFriend(friend_node));
  }
}

TEST_F(FriendHashmapTest, GetFriendSingle) {
  FriendHashmap friend_list;

  friend_list.AddFriend(*friend_one);
  std::string uuid = friend_one->GetUuid();
  std::shared_ptr<FriendNode> node_one = friend_list.GetFriend(uuid);

  EXPECT_EQ(node_one->GetUuid(), friend_one->GetUuid());
}

TEST_F(FriendHashmapTest, GetFriendDouble) {
  FriendHashmap friend_list;

  friend_list.AddFriend(*friend_one);
  friend_list.AddFriend(*friend_two);

  std::shared_ptr<FriendNode> node_one = friend_list.GetFriend(uuid_one);
  std::shared_ptr<FriendNode> node_two = friend_list.GetFriend(uuid_two);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
  EXPECT_EQ(node_two->GetUuid(), uuid_two);
}

TEST_F(FriendHashmapTest, GetFriendMany) {
  FriendHashmap friend_list;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    FriendNode friend_node(uuid, name_one, ip_one, port_one);
    EXPECT_TRUE(friend_list.AddFriend(friend_node));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_EQ(friend_list.GetFriend(uuid)->GetUuid(), uuid);
  }
}

TEST_F(FriendHashmapTest, GetFriendError) {
  FriendHashmap friend_list;

  try {
    friend_list.GetFriend(uuid_one);
    FAIL();
  } catch (const std::out_of_range &err) {
    EXPECT_STREQ("map::at", err.what());
  }
}

TEST_F(FriendHashmapTest, DeleteFriendSingle) {
  FriendHashmap friend_list;

  EXPECT_TRUE(friend_list.AddFriend(*friend_one));
  EXPECT_TRUE(friend_list.DeleteFriend(uuid_one));
}

TEST_F(FriendHashmapTest, DeleteFriendDouble) {
  FriendHashmap friend_list;

  EXPECT_TRUE(friend_list.AddFriend(*friend_one));
  EXPECT_TRUE(friend_list.DeleteFriend(uuid_one));

  EXPECT_TRUE(friend_list.AddFriend(*friend_two));
  EXPECT_TRUE(friend_list.DeleteFriend(uuid_two));
}

TEST_F(FriendHashmapTest, DeleteFriendMany) {
  FriendHashmap friend_list;

  for (int i = 0; i < 100; ++i) {
    EXPECT_TRUE(friend_list.AddFriend(*friend_one));
    EXPECT_TRUE(friend_list.DeleteFriend(uuid_one));
  }
}

TEST_F(FriendHashmapTest, DeleteFriendError) {
  FriendHashmap friend_list;

  EXPECT_FALSE(friend_list.DeleteFriend(uuid_one));
}

TEST_F(FriendHashmapTest, AddDeleteDeleteFriendError) {
  FriendHashmap friend_list;

  EXPECT_TRUE(friend_list.AddFriend(*friend_one));
  EXPECT_TRUE(friend_list.DeleteFriend(uuid_one));
  EXPECT_FALSE(friend_list.DeleteFriend(uuid_one));
}

TEST_F(FriendHashmapTest, GetBegin) {
  FriendHashmap friend_list;

  auto begin = friend_list.GetBegin();

  SUCCEED();
}

TEST_F(FriendHashmapTest, GetEnd) {
  FriendHashmap friend_list;

  auto end = friend_list.GetEnd();

  SUCCEED();
}