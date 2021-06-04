#include "model/friend-functionality/friend-hashmap.h"

#include <gtest/gtest.h>

#include "model/friend-functionality/friend-node.h"

using namespace chat_client_model_friend_functionality;

class FriendHashmapTest : public ::testing::Test {
 public:
  FriendHashmapTest() {}
};

TEST_F(FriendHashmapTest, AddFriendTrue) {
  std::string name = "mitch";
  std::string uuid = "test";
  FriendNode friend_one(&name, &uuid);
  FriendHashmap friend_list;

  EXPECT_TRUE(friend_list.AddFriend(friend_one));
}

TEST_F(FriendHashmapTest, AddFriendDoubleTrue) {
  std::string name = "mitch";
  std::string uuid_one = "test";
  std::string uuid_two = "less";
  FriendNode friend_one(&name, &uuid_one);
  FriendNode friend_two(&name, &uuid_two);
  FriendHashmap friend_list;

  EXPECT_TRUE(friend_list.AddFriend(friend_one));
  EXPECT_TRUE(friend_list.AddFriend(friend_two));
}

TEST_F(FriendHashmapTest, AddFriendFalse) {
  std::string name = "mitch";
  std::string uuid = "test";
  FriendNode friend_one(&name, &uuid);
  FriendNode friend_two(&name, &uuid);
  FriendHashmap friend_list;

  EXPECT_TRUE(friend_list.AddFriend(friend_one));
  EXPECT_FALSE(friend_list.AddFriend(friend_two));
}

TEST_F(FriendHashmapTest, AddFriendDoubleFalse) {
  std::string name = "mitch";
  std::string uuid_one = "test";
  std::string uuid_two = "less";
  FriendNode friend_one(&name, &uuid_one);
  FriendNode friend_two(&name, &uuid_two);
  FriendHashmap friend_list;

  EXPECT_TRUE(friend_list.AddFriend(friend_one));
  EXPECT_TRUE(friend_list.AddFriend(friend_two));
  EXPECT_FALSE(friend_list.AddFriend(friend_one));
  EXPECT_FALSE(friend_list.AddFriend(friend_two));
}