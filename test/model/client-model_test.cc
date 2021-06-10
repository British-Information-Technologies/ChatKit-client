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

TEST_F(FriendClientModelTest, AddFriendManyTrue) {
  ClientModel model;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    FriendNode friend_node(&name, &uuid);
    EXPECT_TRUE(model.AddFriend(friend_node));
  }
}

TEST_F(FriendClientModelTest, AddFriendManyFalse) {
  ClientModel model;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    FriendNode friend_node(&name, &uuid);
    EXPECT_TRUE(model.AddFriend(friend_node));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    FriendNode friend_node(&name, &uuid);
    EXPECT_FALSE(model.AddFriend(friend_node));
  }
}

TEST_F(FriendClientModelTest, GetFriendSingle) {
  ClientModel model;

  model.AddFriend(*friend_one);
  std::string uuid = friend_one->GetUuid();
  std::shared_ptr<FriendNode> node_one = model.GetFriend(uuid);

  EXPECT_EQ(node_one->GetUuid(), friend_one->GetUuid());
}

TEST_F(FriendClientModelTest, GetFriendDouble) {
  ClientModel model;

  model.AddFriend(*friend_one);
  model.AddFriend(*friend_two);

  std::shared_ptr<FriendNode> node_one = model.GetFriend(uuid_one);
  std::shared_ptr<FriendNode> node_two = model.GetFriend(uuid_two);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
  EXPECT_EQ(node_two->GetUuid(), uuid_two);
}

TEST_F(FriendClientModelTest, GetFriendMany) {
  ClientModel model;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    FriendNode friend_node(&name, &uuid);
    EXPECT_TRUE(model.AddFriend(friend_node));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_EQ(model.GetFriend(uuid)->GetUuid(), uuid);
  }
}