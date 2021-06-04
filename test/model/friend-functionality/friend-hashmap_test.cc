#include "model/friend-functionality/friend-hashmap.h"

#include <gtest/gtest.h>

#include "model/friend-functionality/friend-node.h"

using namespace chat_client_model_friend_functionality;

class FriendHashmapTest : public ::testing::Test {
 public:
  FriendHashmapTest() {
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
  FriendNode friend_tmp(&name, &uuid_one);
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
    FriendNode friend_node(&name, &uuid);
    EXPECT_TRUE(friend_list.AddFriend(friend_node));
  }
}

TEST_F(FriendHashmapTest, AddFriendManyFalse) {
  FriendHashmap friend_list;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    FriendNode friend_node(&name, &uuid);
    EXPECT_TRUE(friend_list.AddFriend(friend_node));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    FriendNode friend_node(&name, &uuid);
    EXPECT_FALSE(friend_list.AddFriend(friend_node));
  }
}
