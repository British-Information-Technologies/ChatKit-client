#include "model/client-model.h"

#include <gtest/gtest.h>

#include <string>

#include "model/friend-functionality/friend-node.h"

using namespace chat_client_model;
using namespace chat_client_model_friend_functionality;

class FriendClientModelTest : public ::testing::Test {
 public:
  FriendClientModelTest() {
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

TEST_F(FriendClientModelTest, AddFriendTrue) {
  ClientModel model;

  EXPECT_TRUE(model.AddFriend(*friend_one));
}

TEST_F(FriendClientModelTest, AddFriendDoubleTrue) {
  ClientModel model;

  EXPECT_TRUE(model.AddFriend(*friend_one));
  EXPECT_TRUE(model.AddFriend(*friend_two));
}

TEST_F(FriendClientModelTest, AddFriendFalse) {
  FriendNode friend_tmp(&name, &uuid_one);
  ClientModel model;

  EXPECT_TRUE(model.AddFriend(*friend_one));
  EXPECT_FALSE(model.AddFriend(friend_tmp));
}

TEST_F(FriendClientModelTest, AddFriendDoubleFalse) {
  ClientModel model;

  EXPECT_TRUE(model.AddFriend(*friend_one));
  EXPECT_TRUE(model.AddFriend(*friend_two));
  EXPECT_FALSE(model.AddFriend(*friend_one));
  EXPECT_FALSE(model.AddFriend(*friend_two));
}