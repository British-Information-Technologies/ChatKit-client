#include "model/client-model.h"

#include <gtest/gtest.h>

#include <string>

#include "model/friend-functionality/friend-node.h"

using namespace chat_client_model;
using namespace chat_client_model_friend_functionality;

class FriendClientModelTest : public ::testing::Test {};

TEST_F(FriendClientModelTest, AddFriendTrue) {
  ClientModel model;
  std::string name = "mitch";
  std::string uuid = "test";

  FriendNode *friend_one = new FriendNode(&name, &uuid);

  EXPECT_TRUE(model.AddFriend(*friend_one));

  delete friend_one;
}