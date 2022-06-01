#include "model/server-functionality/server-utility.h"

#include <gtest/gtest.h>

#include <string>

#include "model/server-functionality/server-node.h"

using namespace model_server_functionality;

class ServerUtilityTest : public ::testing::Test {
 public:
  ServerUtilityTest() {
    name_one = "mitch";
    name_two = "micky";

    uuid_one = "test";
    uuid_two = "less";

    owner_one = "o1";
    owner_two = "o2";

    ip_one = "localhost-one";
    ip_two = "localhost-two";

    port_one = "1234";
    port_two = "5678";
    
    server_one = new ServerNode(uuid_one, name_one, owner_one, ip_one, port_one);
    server_two = new ServerNode(uuid_two, name_two, owner_two, ip_two, port_two);
  }

 protected:
  std::string name_one;
  std::string name_two;

  std::string uuid_one;
  std::string uuid_two;
  
  std::string owner_one;
  std::string owner_two;

  std::string ip_one = "localhost-one";
  std::string ip_two = "localhost-two";

  std::string port_one = "1234";
  std::string port_two = "5678";

  ServerNode *server_one;
  ServerNode *server_two;
};

TEST_F(ServerUtilityTest, AddServerTrue) {
  ServerUtility utility;
  EXPECT_TRUE(utility.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
}

TEST_F(ServerUtilityTest, AddServerDoubleTrue) {
  ServerUtility utility;

  EXPECT_TRUE(utility.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
  EXPECT_TRUE(utility.AddServer(uuid_two, name_two, owner_two, ip_two, port_two));
}

TEST_F(ServerUtilityTest, AddServerFalse) {
  ServerUtility utility;

  EXPECT_TRUE(utility.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
  EXPECT_FALSE(utility.AddServer(uuid_one, name_one, owner_two, ip_two, port_two));
}

TEST_F(ServerUtilityTest, AddServerDoubleFalse) {
  ServerUtility utility;

  EXPECT_TRUE(utility.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
  EXPECT_TRUE(utility.AddServer(uuid_two, name_two, owner_two, ip_two, port_two));
  EXPECT_FALSE(utility.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
  EXPECT_FALSE(utility.AddServer(uuid_two, name_two, owner_two, ip_two, port_two));
}

TEST_F(ServerUtilityTest, AddServerManyTrue) {
  ServerUtility utility;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(utility.AddServer(uuid, name_one, owner_one, ip_one, port_one));
  }
}

TEST_F(ServerUtilityTest, AddServerManyFalse) {
  ServerUtility utility;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(utility.AddServer(uuid, name_one, owner_one, ip_one, port_one));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_FALSE(utility.AddServer(uuid, name_one, owner_one, ip_one, port_one));
  }
}

TEST_F(ServerUtilityTest, GetServerSingle) {
  ServerUtility utility;

  utility.AddServer(uuid_one, name_one, owner_one, ip_one, port_one);
  std::shared_ptr<ServerNode> node_one = utility.GetServer(uuid_one);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
}

TEST_F(ServerUtilityTest, GetServerDouble) {
  ServerUtility utility;

  utility.AddServer(uuid_one, name_one, owner_one, ip_one, port_one);
  utility.AddServer(uuid_two, name_two, owner_two, ip_two, port_two);

  std::shared_ptr<ServerNode> node_one = utility.GetServer(uuid_one);
  std::shared_ptr<ServerNode> node_two = utility.GetServer(uuid_two);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
  EXPECT_EQ(node_two->GetUuid(), uuid_two);
}

TEST_F(ServerUtilityTest, GetServerMany) {
  ServerUtility utility;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(utility.AddServer(uuid, name_one, owner_one, ip_one, port_one));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_EQ(utility.GetServer(uuid)->GetUuid(), uuid);
  }
}

TEST_F(ServerUtilityTest, GetServerError) {
  ServerUtility utility;

  try {
    utility.GetServer(uuid_one);
    FAIL();
  } catch (const std::out_of_range &err) {
    EXPECT_STREQ("map::at", err.what());
  }
}

TEST_F(ServerUtilityTest, DeleteServerSingle) {
  ServerUtility utility;

  EXPECT_TRUE(utility.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
  EXPECT_TRUE(utility.DeleteServer(uuid_one));
}

TEST_F(ServerUtilityTest, DeleteServerDouble) {
  ServerUtility utility;

  EXPECT_TRUE(utility.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
  EXPECT_TRUE(utility.DeleteServer(uuid_one));

  EXPECT_TRUE(utility.AddServer(uuid_two, name_two, owner_two, ip_two, port_two));
  EXPECT_TRUE(utility.DeleteServer(uuid_two));
}

TEST_F(ServerUtilityTest, DeleteServerMany) {
  ServerUtility utility;

  for (int i = 0; i < 100; ++i) {
    EXPECT_TRUE(utility.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
    EXPECT_TRUE(utility.DeleteServer(uuid_one));
  }
}

TEST_F(ServerUtilityTest, DeleteServerError) {
  ServerUtility utility;

  EXPECT_FALSE(utility.DeleteServer(uuid_one));
}

TEST_F(ServerUtilityTest, AddDeleteDeleteServerError) {
  ServerUtility utility;

  EXPECT_TRUE(utility.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
  EXPECT_TRUE(utility.DeleteServer(uuid_one));
  EXPECT_FALSE(utility.DeleteServer(uuid_one));
}

TEST_F(ServerUtilityTest, Begin) {
  ServerUtility utility;

  auto begin = utility.Begin();

  SUCCEED();
}

TEST_F(ServerUtilityTest, End) {
  ServerUtility utility;

  auto begin = utility.End();

  SUCCEED();
}