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
  
  ServerNode *server_one;
  ServerNode *server_two;

  std::string ip_one;
  std::string ip_two;

  std::string port_one;
  std::string port_two;
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

  ServerNode tmp_server(uuid, name, owner, ip_one, port_one);

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
    servers_array[index] = new ServerNode(uuid, name, owner, ip_one, port_one);
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

  ServerNode *tmp_server = new ServerNode(uuid, name, owner, ip_one, port_one);

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

  ServerNode tmp_server(uuid, name, owner, ip_one, port_one);

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
    servers_array[index] = new ServerNode(uuid, name, owner, ip_one, port_one);
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

  ServerNode *tmp_server = new ServerNode(uuid, name, owner, ip_one, port_one);

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
  
  ServerNode tmp_server(uuid, name, owner, ip_one, port_one);

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
    servers_array[index] = new ServerNode(uuid, name, owner, ip_one, port_one);
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

  ServerNode *tmp_server = new ServerNode(uuid, name, owner, ip_one, port_one);

  EXPECT_EQ(server_one->GetOwner(), tmp_server->GetOwner());
}

TEST_F(ServerNodeTest, GetIp) { EXPECT_EQ(server_one->GetIp(), ip_one); }

TEST_F(ServerNodeTest, GetIpDouble) {
  EXPECT_EQ(server_one->GetIp(), ip_one);
  EXPECT_EQ(server_two->GetIp(), ip_two);
}

TEST_F(ServerNodeTest, GetIpConstant) {
  std::string name = "mitch";
  std::string uuid = "1234";
  std::string owner = "o5";
  std::string ip = "localhost-one";
  
  ServerNode tmp_server(uuid, name, owner, ip, port_one);

  EXPECT_EQ(tmp_server.GetIp(), ip);

  ip = "bob";
  EXPECT_NE(tmp_server.GetIp(), ip);

  ip = "localhost-one";
  EXPECT_EQ(tmp_server.GetIp(), ip);
}

TEST_F(ServerNodeTest, GetIpMany) {
  ServerNode *servers_array[20];
  std::string uuid = "1234";
  std::string name = "mitch";
  std::string owner = "bob";

  for (int index = 0; index < 20; ++index) {
    std::string ip = std::to_string(index);
    servers_array[index] = new ServerNode(uuid, name, owner, ip, port_one);
  }

  for (int index = 0; index < 20; ++index) {
    EXPECT_EQ(servers_array[index]->GetIp(), std::to_string(index));
  }
}

TEST_F(ServerNodeTest, GetIpNotEqual) {
  EXPECT_NE(server_one->GetIp(), server_two->GetIp());
}

TEST_F(ServerNodeTest, GetIpEqual) {
  std::string name = "mitch";
  std::string uuid = "1234";
  std::string owner = "o1";
  std::string ip = "localhost-one";

  ServerNode *tmp_server = new ServerNode(uuid, name, owner, ip, port_one);

  EXPECT_EQ(server_one->GetIp(), tmp_server->GetIp());
}

TEST_F(ServerNodeTest, GetPort) { EXPECT_EQ(server_one->GetPort(), port_one); }

TEST_F(ServerNodeTest, GetPortDouble) {
  EXPECT_EQ(server_one->GetPort(), port_one);
  EXPECT_EQ(server_two->GetPort(), port_two);
}

TEST_F(ServerNodeTest, GetPortConstant) {
  std::string name = "mitch";
  std::string uuid = "1234";
  std::string owner = "o5";
  std::string ip = "localhost-one";
  std::string port = "1234";
  
  ServerNode tmp_server(uuid, name, owner, ip, port);

  EXPECT_EQ(tmp_server.GetPort(), port);

  port = "bob";
  EXPECT_NE(tmp_server.GetPort(), port);

  port = "1234";
  EXPECT_EQ(tmp_server.GetPort(), port);
}

TEST_F(ServerNodeTest, GetPortMany) {
  ServerNode *servers_array[20];
  std::string uuid = "1234";
  std::string name = "mitch";
  std::string owner = "bob";
  std::string ip = "localhost-one";

  for (int index = 0; index < 20; ++index) {
    std::string port = std::to_string(index);
    servers_array[index] = new ServerNode(uuid, name, owner, ip, port);
  }

  for (int index = 0; index < 20; ++index) {
    EXPECT_EQ(servers_array[index]->GetPort(), std::to_string(index));
  }
}

TEST_F(ServerNodeTest, GetPortNotEqual) {
  EXPECT_NE(server_one->GetPort(), server_two->GetPort());
}

TEST_F(ServerNodeTest, GetPortEqual) {
  std::string name = "mitch";
  std::string uuid = "1234";
  std::string owner = "o1";
  std::string ip = "localhost-one";
  std::string port = "1234";

  ServerNode *tmp_server = new ServerNode(uuid, name, owner, ip, port);

  EXPECT_EQ(server_one->GetPort(), tmp_server->GetPort());
}