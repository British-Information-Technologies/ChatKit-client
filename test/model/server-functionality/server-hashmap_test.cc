#include "model/server-functionality/server-hashmap.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <stdexcept>

#include "model/server-functionality/server-node.h"

using namespace model_server_functionality;

class ServerHashmapTest : public ::testing::Test {
 public:
  ServerHashmapTest() {
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

TEST_F(ServerHashmapTest, AddServerTrue) {
  ServerHashmap server_list;

  EXPECT_TRUE(server_list.AddServer(*server_one));
}
 
TEST_F(ServerHashmapTest, AddServerDoubleTrue) {
  ServerHashmap server_list;

  EXPECT_TRUE(server_list.AddServer(*server_one));
  EXPECT_TRUE(server_list.AddServer(*server_two));
}

TEST_F(ServerHashmapTest, AddServerFalse) {
  ServerNode server_tmp(uuid_one, name_one, owner_one, ip_one, port_one);
  ServerHashmap server_list;

  EXPECT_TRUE(server_list.AddServer(*server_one));
  EXPECT_FALSE(server_list.AddServer(server_tmp));
}

TEST_F(ServerHashmapTest, AddServerDoubleFalse) {
  ServerHashmap server_list;

  EXPECT_TRUE(server_list.AddServer(*server_one));
  EXPECT_TRUE(server_list.AddServer(*server_two));
  EXPECT_FALSE(server_list.AddServer(*server_one));
  EXPECT_FALSE(server_list.AddServer(*server_two));
}

TEST_F(ServerHashmapTest, AddServerManyTrue) {
  ServerHashmap server_list;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    ServerNode server_node(uuid, name_one, owner_one, ip_one, port_one);
    EXPECT_TRUE(server_list.AddServer(server_node));
  }
}

TEST_F(ServerHashmapTest, AddServerManyFalse) {
  ServerHashmap server_list;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    ServerNode server_node(uuid, name_one, owner_one, ip_one, port_one);
    EXPECT_TRUE(server_list.AddServer(server_node));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    ServerNode server_node(uuid, name_one, owner_one, ip_one, port_one);
    EXPECT_FALSE(server_list.AddServer(server_node));
  }
}

TEST_F(ServerHashmapTest, GetServerSingle) {
  ServerHashmap server_list;

  server_list.AddServer(*server_one);
  std::string uuid = server_one->GetUuid();
  std::shared_ptr<ServerNode> node_one = server_list.GetServer(uuid);

  EXPECT_EQ(node_one->GetUuid(), server_one->GetUuid());
}

TEST_F(ServerHashmapTest, GetServerDouble) {
  ServerHashmap server_list;

  server_list.AddServer(*server_one);
  server_list.AddServer(*server_two);

  std::shared_ptr<ServerNode> node_one = server_list.GetServer(uuid_one);
  std::shared_ptr<ServerNode> node_two = server_list.GetServer(uuid_two);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
  EXPECT_EQ(node_two->GetUuid(), uuid_two);
}

TEST_F(ServerHashmapTest, GetServerMany) {
  ServerHashmap server_list;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    ServerNode server_node(uuid, name_one, owner_one, ip_one, port_one);
    EXPECT_TRUE(server_list.AddServer(server_node));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_EQ(server_list.GetServer(uuid)->GetUuid(), uuid);
  }
}

TEST_F(ServerHashmapTest, GetServerError) {
  ServerHashmap server_list;

  try {
    server_list.GetServer(uuid_one);
    FAIL();
  } catch (const std::out_of_range &err) {
    EXPECT_STREQ("map::at", err.what());
  }
}

TEST_F(ServerHashmapTest, DeleteServerSingle) {
  ServerHashmap server_list;

  EXPECT_TRUE(server_list.AddServer(*server_one));
  EXPECT_TRUE(server_list.DeleteServer(uuid_one));
}

TEST_F(ServerHashmapTest, DeleteServerDouble) {
  ServerHashmap server_list;

  EXPECT_TRUE(server_list.AddServer(*server_one));
  EXPECT_TRUE(server_list.DeleteServer(uuid_one));

  EXPECT_TRUE(server_list.AddServer(*server_two));
  EXPECT_TRUE(server_list.DeleteServer(uuid_two));
}

TEST_F(ServerHashmapTest, DeleteServerMany) {
  ServerHashmap server_list;

  for (int i = 0; i < 100; ++i) {
    EXPECT_TRUE(server_list.AddServer(*server_one));
    EXPECT_TRUE(server_list.DeleteServer(uuid_one));
  }
}

TEST_F(ServerHashmapTest, DeleteServerError) {
  ServerHashmap server_list;

  EXPECT_FALSE(server_list.DeleteServer(uuid_one));
}

TEST_F(ServerHashmapTest, AddDeleteDeleteServerError) {
  ServerHashmap server_list;

  EXPECT_TRUE(server_list.AddServer(*server_one));
  EXPECT_TRUE(server_list.DeleteServer(uuid_one));
  EXPECT_FALSE(server_list.DeleteServer(uuid_one));
}

TEST_F(ServerHashmapTest, GetBegin) {
  ServerHashmap server_list;

  auto begin = server_list.GetBegin();

  SUCCEED();
}

TEST_F(ServerHashmapTest, GetEnd) {
  ServerHashmap server_list;

  auto end = server_list.GetEnd();

  SUCCEED();
}