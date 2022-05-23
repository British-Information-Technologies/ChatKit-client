#include "model/server-functionality/server-node.h"

#include <gtest/gtest.h>

#include <iostream>
#include <string>

using namespace model_server_functionality;

class ServerNodeTest : public ::testing::Test {
 public:
  ServerNodeTest() {
    name_one = "mitch";
    name_two = "micky";

    uuid_one = "testtesttest1234567890";
    uuid_two = "testtest1234567890";

    owner_one = "o1";
    owner_two = "o2";

    server_one = new ServerNode(uuid_one, name_one, owner_one);
    server_two = new ServerNode(uuid_two, name_two, owner_two);
  }

 protected:
  std::string name_one;
  std::string name_two;

  std::string uuid_one;
  std::string uuid_two;

  std::string owner_one;
  std::string owner_two;
  
  ServerNode *server_one;
  ServerNode *server_two;
};

TEST_F(ServerNodeTest, GetName) { EXPECT_EQ(server_one->GetName(), name_one); }

TEST_F(ServerNodeTest, GetNameDouble) {
  EXPECT_EQ(server_one->GetName(), name_one);
  EXPECT_EQ(server_two->GetName(), name_two);
}

TEST_F(ServerNodeTest, GetNameConstant) {
  std::string name = "mitch";
  std::string uuid = "1234";
  std::string owner = "o5";

  ServerNode tmp_server(uuid, name, owner);

  EXPECT_EQ(tmp_server.GetName(), name);

  name = "bob";
  EXPECT_NE(tmp_server.GetName(), name);

  name = "mitch";
  EXPECT_EQ(tmp_server.GetName(), name);
}

TEST_F(ServerNodeTest, GetNameMany) {
  ServerNode *servers_array[20];
  std::string uuid = "1234";
  std::string owner = "o5";

  for (int index = 0; index < 20; ++index) {
    std::string name = std::to_string(index);
    servers_array[index] = new ServerNode(uuid, name, owner);
  }

  for (int index = 0; index < 20; ++index) {
    EXPECT_EQ(servers_array[index]->GetName(), std::to_string(index));
  }
}

TEST_F(ServerNodeTest, GetNameNotEqual) {
  EXPECT_NE(server_one->GetName(), server_two->GetName());
}

TEST_F(ServerNodeTest, GetNameEqual) {
  std::string name = "mitch";
  std::string uuid = "1234";
  std::string owner = "o5";

  ServerNode *tmp_server = new ServerNode(uuid, name, owner);

  EXPECT_EQ(server_one->GetName(), tmp_server->GetName());
}

TEST_F(ServerNodeTest, GetUuid) {
  std::string uuid = "testtesttest1234567890";
  EXPECT_EQ(server_one->GetUuid(), uuid);
}

TEST_F(ServerNodeTest, GetUuidDouble) {
  EXPECT_EQ(server_one->GetUuid(), uuid_one);
  EXPECT_EQ(server_two->GetUuid(), uuid_two);
}

TEST_F(ServerNodeTest, GetUuidConstant) {
  std::string name = "mitch";
  std::string uuid = "1234";
  std::string owner = "o5";

  ServerNode tmp_server(uuid, name, owner);

  EXPECT_EQ(tmp_server.GetUuid(), uuid);

  uuid = "12";
  EXPECT_NE(tmp_server.GetUuid(), uuid);

  uuid = "1234";
  EXPECT_EQ(tmp_server.GetUuid(), uuid);
}

TEST_F(ServerNodeTest, GetUuidMany) {
  ServerNode *servers_array[20];
  std::string name = "mitch";
  std::string owner = "o5";

  for (int index = 0; index < 20; ++index) {
    std::string uuid = std::to_string(index);
    servers_array[index] = new ServerNode(uuid, name, owner);
  }

  for (int index = 0; index < 20; ++index) {
    EXPECT_EQ(servers_array[index]->GetUuid(), std::to_string(index));
  }
}

TEST_F(ServerNodeTest, GetUuidNotEqual) {
  EXPECT_NE(server_one->GetUuid(), server_two->GetUuid());
}

TEST_F(ServerNodeTest, GetUuidEqual) {
  std::string name = "jeff";
  std::string uuid = "testtesttest1234567890";
  std::string owner = "o5";

  ServerNode *tmp_server = new ServerNode(uuid, name, owner);

  EXPECT_EQ(server_one->GetUuid(), tmp_server->GetUuid());
}

TEST_F(ServerNodeTest, GetOwner) { EXPECT_EQ(server_one->GetOwner(), owner_one); }

TEST_F(ServerNodeTest, GetOwnerDouble) {
  EXPECT_EQ(server_one->GetOwner(), owner_one);
  EXPECT_EQ(server_two->GetOwner(), owner_two);
}

TEST_F(ServerNodeTest, GetOwnerConstant) {
  std::string name = "mitch";
  std::string uuid = "1234";
  std::string owner = "o5";
  
  ServerNode tmp_server(uuid, name, owner);

  EXPECT_EQ(tmp_server.GetOwner(), owner);

  owner = "bob";
  EXPECT_NE(tmp_server.GetOwner(), owner);

  owner = "o5";
  EXPECT_EQ(tmp_server.GetOwner(), owner);
}

TEST_F(ServerNodeTest, GetOwnerMany) {
  ServerNode *servers_array[20];
  std::string uuid = "1234";
  std::string name = "mitch";

  for (int index = 0; index < 20; ++index) {
    std::string owner = std::to_string(index);
    servers_array[index] = new ServerNode(uuid, name, owner);
  }

  for (int index = 0; index < 20; ++index) {
    EXPECT_EQ(servers_array[index]->GetOwner(), std::to_string(index));
  }
}

TEST_F(ServerNodeTest, GetOwnerNotEqual) {
  EXPECT_NE(server_one->GetOwner(), server_two->GetOwner());
}

TEST_F(ServerNodeTest, GetOwnerEqual) {
  std::string name = "mitch";
  std::string uuid = "1234";
  std::string owner = "o1";

  ServerNode *tmp_server = new ServerNode(uuid, name, owner);

  EXPECT_EQ(server_one->GetOwner(), tmp_server->GetOwner());
}