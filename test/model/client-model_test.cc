#include "model/client-model.h"

#include <gtest/gtest.h>

#include <string>

#include "model/friend-functionality/friend-node.h"
#include "model/server-functionality/server-node.h"

using namespace model;
using namespace model_friend_functionality;
using namespace model_server_functionality;

/* TODO: add name to the addFirend method call */

class FriendClientModelTest : public ::testing::Test {
 public:
  FriendClientModelTest() {
    name_one = "mitch";
    name_two = "micky";

    uuid_one = "test";
    uuid_two = "less";
  }

 protected:
  std::string name_one;
  std::string name_two;

  std::string uuid_one;
  std::string uuid_two;
};

TEST_F(FriendClientModelTest, AddFriendTrue) {
  ClientModel model;

  bool ret = model.AddFriend(uuid_one, name_one);

  EXPECT_TRUE(ret);
}

TEST_F(FriendClientModelTest, AddFriendDoubleTrue) {
  ClientModel model;

  EXPECT_TRUE(model.AddFriend(uuid_one, name_one));
  EXPECT_TRUE(model.AddFriend(uuid_two, name_two));
}

TEST_F(FriendClientModelTest, AddFriendFalse) {
  ClientModel model;

  EXPECT_TRUE(model.AddFriend(uuid_one, name_one));
  EXPECT_FALSE(model.AddFriend(uuid_one, name_one));
}

TEST_F(FriendClientModelTest, AddFriendDoubleFalse) {
  ClientModel model;

  EXPECT_TRUE(model.AddFriend(uuid_one, name_one));
  EXPECT_TRUE(model.AddFriend(uuid_two, name_two));
  EXPECT_FALSE(model.AddFriend(uuid_one, name_one));
  EXPECT_FALSE(model.AddFriend(uuid_two, name_two));
}

TEST_F(FriendClientModelTest, AddFriendManyTrue) {
  ClientModel model;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(model.AddFriend(uuid, name_one));
  }
}

TEST_F(FriendClientModelTest, AddFriendManyFalse) {
  ClientModel model;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(model.AddFriend(uuid, name_one));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_FALSE(model.AddFriend(uuid, name_one));
  }
}

TEST_F(FriendClientModelTest, GetFriendSingle) {
  ClientModel model;

  model.AddFriend(uuid_one, name_one);
  std::shared_ptr<FriendNode> node_one = model.GetFriend(uuid_one);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
}

TEST_F(FriendClientModelTest, GetFriendDouble) {
  ClientModel model;

  model.AddFriend(uuid_one, name_one);
  model.AddFriend(uuid_two, name_two);

  std::shared_ptr<FriendNode> node_one = model.GetFriend(uuid_one);
  std::shared_ptr<FriendNode> node_two = model.GetFriend(uuid_two);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
  EXPECT_EQ(node_two->GetUuid(), uuid_two);
}

TEST_F(FriendClientModelTest, GetFriendMany) {
  ClientModel model;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(model.AddFriend(uuid, name_one));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_EQ(model.GetFriend(uuid)->GetUuid(), uuid);
  }
}

TEST_F(FriendClientModelTest, GetFriendError) {
  ClientModel model;

  try {
    model.GetFriend(uuid_one);
    FAIL();
  } catch (const std::out_of_range &err) {
    EXPECT_STREQ("map::at", err.what());
  }
}

TEST_F(FriendClientModelTest, DeleteFriendSingle) {
  ClientModel model;

  EXPECT_TRUE(model.AddFriend(uuid_one, name_one));
  EXPECT_TRUE(model.DeleteFriend(uuid_one));
}

TEST_F(FriendClientModelTest, DeleteFriendDouble) {
  ClientModel model;

  EXPECT_TRUE(model.AddFriend(uuid_one, name_one));
  EXPECT_TRUE(model.DeleteFriend(uuid_one));

  EXPECT_TRUE(model.AddFriend(uuid_two, name_two));
  EXPECT_TRUE(model.DeleteFriend(uuid_two));
}

TEST_F(FriendClientModelTest, DeleteFriendMany) {
  ClientModel model;

  for (int i = 0; i < 100; ++i) {
    EXPECT_TRUE(model.AddFriend(uuid_one, name_one));
    EXPECT_TRUE(model.DeleteFriend(uuid_one));
  }
}

TEST_F(FriendClientModelTest, DeleteFriendError) {
  ClientModel model;

  EXPECT_FALSE(model.DeleteFriend(uuid_one));
}

TEST_F(FriendClientModelTest, AddDeleteDeleteFriendError) {
  ClientModel model;

  EXPECT_TRUE(model.AddFriend(uuid_one, name_two));
  EXPECT_TRUE(model.DeleteFriend(uuid_one));
  EXPECT_FALSE(model.DeleteFriend(uuid_one));
}


/* ----------------------------------------------------- */


class ServerClientModelTest : public ::testing::Test {
 public:
  ServerClientModelTest() {
    name_one = "mitch";
    name_two = "micky";

    uuid_one = "test";
    uuid_two = "less";

    owner_one = "o1";
    owner_two = "o2";
  }

 protected:
  std::string name_one;
  std::string name_two;

  std::string uuid_one;
  std::string uuid_two;

  std::string owner_one;
  std::string owner_two;
};

TEST_F(ServerClientModelTest, AddServerTrue) {
  ClientModel model;

  bool ret = model.AddServer(uuid_one, name_one, owner_one);

  EXPECT_TRUE(ret);
}

TEST_F(ServerClientModelTest, AddServerDoubleTrue) {
  ClientModel model;

  EXPECT_TRUE(model.AddServer(uuid_one, name_one, owner_one));
  EXPECT_TRUE(model.AddServer(uuid_two, name_two, owner_two));
}

TEST_F(ServerClientModelTest, AddServerFalse) {
  ClientModel model;

  EXPECT_TRUE(model.AddServer(uuid_one, name_one, owner_one));
  EXPECT_FALSE(model.AddServer(uuid_one, name_one, owner_one));
}

TEST_F(ServerClientModelTest, AddServerDoubleFalse) {
  ClientModel model;

  EXPECT_TRUE(model.AddServer(uuid_one, name_one, owner_one));
  EXPECT_TRUE(model.AddServer(uuid_two, name_two, owner_two));
  EXPECT_FALSE(model.AddServer(uuid_one, name_one, owner_one));
  EXPECT_FALSE(model.AddServer(uuid_two, name_two, owner_two));
}

TEST_F(ServerClientModelTest, AddServerManyTrue) {
  ClientModel model;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(model.AddServer(uuid, name_one, owner_one));
  }
}

TEST_F(ServerClientModelTest, AddServerManyFalse) {
  ClientModel model;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(model.AddServer(uuid, name_one, owner_one));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_FALSE(model.AddServer(uuid, name_one, owner_one));
  }
}

TEST_F(ServerClientModelTest, GetServerSingle) {
  ClientModel model;

  model.AddServer(uuid_one, name_one, owner_one);
  std::shared_ptr<ServerNode> node_one = model.GetServer(uuid_one);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
}

TEST_F(ServerClientModelTest, GetServerDouble) {
  ClientModel model;

  model.AddServer(uuid_one, name_one, owner_one);
  model.AddServer(uuid_two, name_two, owner_two);

  std::shared_ptr<ServerNode> node_one = model.GetServer(uuid_one);
  std::shared_ptr<ServerNode> node_two = model.GetServer(uuid_two);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
  EXPECT_EQ(node_two->GetUuid(), uuid_two);
}

TEST_F(ServerClientModelTest, GetServerMany) {
  ClientModel model;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(model.AddServer(uuid, name_one, owner_one));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_EQ(model.GetServer(uuid)->GetUuid(), uuid);
  }
}

TEST_F(ServerClientModelTest, GetServerError) {
  ClientModel model;

  try {
    model.GetServer(uuid_one);
    FAIL();
  } catch (const std::out_of_range &err) {
    EXPECT_STREQ("map::at", err.what());
  }
}

TEST_F(ServerClientModelTest, DeleteServerSingle) {
  ClientModel model;

  EXPECT_TRUE(model.AddServer(uuid_one, name_one, owner_one));
  EXPECT_TRUE(model.DeleteServer(uuid_one));
}

TEST_F(ServerClientModelTest, DeleteServerDouble) {
  ClientModel model;

  EXPECT_TRUE(model.AddServer(uuid_one, name_one, owner_one));
  EXPECT_TRUE(model.DeleteServer(uuid_one));

  EXPECT_TRUE(model.AddServer(uuid_two, name_two, owner_two));
  EXPECT_TRUE(model.DeleteServer(uuid_two));
}

TEST_F(ServerClientModelTest, DeleteServerMany) {
  ClientModel model;

  for (int i = 0; i < 100; ++i) {
    EXPECT_TRUE(model.AddServer(uuid_one, name_one, owner_one));
    EXPECT_TRUE(model.DeleteServer(uuid_one));
  }
}

TEST_F(ServerClientModelTest, DeleteServerError) {
  ClientModel model;

  EXPECT_FALSE(model.DeleteServer(uuid_one));
}

TEST_F(ServerClientModelTest, AddDeleteDeleteServerError) {
  ClientModel model;

  EXPECT_TRUE(model.AddServer(uuid_one, name_two, owner_one));
  EXPECT_TRUE(model.DeleteServer(uuid_one));
  EXPECT_FALSE(model.DeleteServer(uuid_one));
}