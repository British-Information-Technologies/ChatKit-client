#include "model/friend-functionality/friend-node.h"

#include <gtest/gtest.h>

#include <iostream>
#include <string>

using namespace chat_client_model_friend_functionality;

class FriendNodeTest : public ::testing::Test {
 public:
  FriendNodeTest() {
    std::string name_one = "mitch";
    std::string name_two = "micky";

    std::string uuid_one = "testtesttest1234567890";
    std::string uuid_two = "testtest1234567890";

    friend_one = new FriendNode(&name_one, &uuid_one);
    friend_two = new FriendNode(&name_two, &uuid_two);
  }

 protected:
  std::string name_one = "mitch";
  std::string name_two = "micky";
  std::string uuid_one = "testtesttest1234567890";
  std::string uuid_two = "testtest1234567890";
  FriendNode *friend_one;
  FriendNode *friend_two;
};

TEST_F(FriendNodeTest, GetName) { EXPECT_EQ(friend_one->GetName(), name_one); }

TEST_F(FriendNodeTest, GetNameDouble) {
  EXPECT_EQ(friend_one->GetName(), name_one);
  EXPECT_EQ(friend_two->GetName(), name_two);
}

TEST_F(FriendNodeTest, GetNameConstant) {
  std::string name = "mitch";
  std::string uuid = "1234";
  FriendNode tmp_friend(&name, &uuid);

  EXPECT_EQ(tmp_friend.GetName(), name);

  name = "bob";
  EXPECT_NE(tmp_friend.GetName(), name);

  name = "mitch";
  EXPECT_EQ(tmp_friend.GetName(), name);
}

TEST_F(FriendNodeTest, GetNameMany) {
  FriendNode *friends_array[20];
  std::string uuid = "1234";

  for (int index = 0; index < 20; ++index) {
    std::string name = std::to_string(index);
    friends_array[index] = new FriendNode(&name, &uuid);
  }

  for (int index = 0; index < 20; ++index) {
    EXPECT_EQ(friends_array[index]->GetName(), std::to_string(index));
  }
}

TEST_F(FriendNodeTest, GetNameNotEqual) {
  EXPECT_NE(friend_one->GetName(), friend_two->GetName());
}

TEST_F(FriendNodeTest, GetNameEqual) {
  std::string name = "mitch";
  std::string uuid = "1234";
  FriendNode *tmp_friend = new FriendNode(&name, &uuid);

  EXPECT_EQ(friend_one->GetName(), tmp_friend->GetName());
}

TEST_F(FriendNodeTest, GetUuid) {
  std::string uuid = "testtesttest1234567890";
  EXPECT_EQ(friend_one->GetUuid(), uuid);
}

TEST_F(FriendNodeTest, GetUuidDouble) {
  EXPECT_EQ(friend_one->GetUuid(), uuid_one);
  EXPECT_EQ(friend_two->GetUuid(), uuid_two);
}

TEST_F(FriendNodeTest, GetUuidConstant) {
  std::string name = "mitch";
  std::string uuid = "1234";
  FriendNode tmp_friend(&name, &uuid);

  EXPECT_EQ(tmp_friend.GetUuid(), uuid);

  uuid = "12";
  EXPECT_NE(tmp_friend.GetUuid(), uuid);

  uuid = "1234";
  EXPECT_EQ(tmp_friend.GetUuid(), uuid);
}