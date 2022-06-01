#include "model/client-model.h"

#include <gtest/gtest.h>

#include <string>

#include "model/friend-functionality/friend-node.h"
#include "model/server-functionality/server-node.h"
#include "networking/temporary-server.h"
#include "networking/temporary-client.h"

using namespace model;
using namespace model_friend_functionality;
using namespace model_server_functionality;

class ClientModelTest : public ::testing::Test {
 public:
  ClientModelTest() {
    server_uuid = "test1234";
    server_name = "Test Server";
    server_owner = "mitch";
    server_ip = "localhost";
    server_port = "3490";

    friend_uuid = "test1234";
    friend_name = "Test Server";
    friend_ip = "localhost";
    friend_port = "3490";
  }

 protected:
  std::string server_uuid;
  std::string server_name;
  std::string server_owner;
  std::string server_ip;
  std::string server_port;

  std::string friend_uuid;
  std::string friend_name;
  std::string friend_ip;
  std::string friend_port;
};

TEST_F(ClientModelTest, LoadConnectionsEmpty) {
  ClientModel model;

  auto connections = model.LoadConnections();

  EXPECT_EQ(connections.size(), 0);
}

TEST_F(ClientModelTest, LoadServerConnectionsSingle) {
  ClientModel model;

  TemporaryServer listen_server(server_ip, server_port);
  
  int result = listen_server.SetUp();
  
  EXPECT_EQ(result, 1);

  bool ret = model.AddServer(server_uuid, server_name, server_owner, server_ip, server_port);

  EXPECT_TRUE(ret);

  auto connections = model.LoadConnections();

  EXPECT_EQ(connections.size(), 1);

  listen_server.TearDown();
}

TEST_F(ClientModelTest, LoadServerConnectionsMany) {
  ClientModel model;

  std::map<int, std::shared_ptr<TemporaryServer>> tmp;

  for(int i = 0; i < 4; ++i) {
    int tmp_port = stoi(server_port) + i;
    std::string port = std::to_string(tmp_port);
    std::shared_ptr<TemporaryServer> listen_server = std::make_shared<TemporaryServer>(server_ip, port);

    tmp.insert(std::pair<int, std::shared_ptr<TemporaryServer>>(i, listen_server));
    
    int result = listen_server->SetUp();

    EXPECT_EQ(result, 1);

    bool ret = model.AddServer(std::to_string(i), server_name, server_owner, server_ip, port);

    EXPECT_TRUE(ret);
  }
  
  auto connections = model.LoadConnections();

  EXPECT_EQ(connections.size(), 4);

  for (auto it = tmp.begin(); it != tmp.end(); ++it) {
    it->second->TearDown();
  }
}

/* ---- TODO: fix client connections --- */
// TEST_F(ClientModelTest, LoadClientConnectionsSingle) {
//   ClientModel model;

//   TemporaryClient listen_client(friend_ip, friend_port);
  
//   listen_client.Listen();

//   bool ret = model.AddFriend(friend_uuid, friend_name, friend_ip, friend_port);

//   EXPECT_TRUE(ret);

//   auto connections = model.LoadConnections();

//   EXPECT_EQ(connections.size(), 1);

//   listen_client.TearDown();
// }

// TEST_F(ClientModelTest, LoadClientConnectionsMany) {
//   ClientModel model;

//   std::map<int, std::shared_ptr<TemporaryServer>> tmp;

//   for(int i = 0; i < 4; ++i) {
//     int tmp_port = stoi(server_port) + i;
//     std::string port = std::to_string(tmp_port);
//     std::shared_ptr<TemporaryServer> listen_server = std::make_shared<TemporaryServer>(server_ip, port);

//     tmp.insert(std::pair<int, std::shared_ptr<TemporaryServer>>(i, listen_server));
    
//     int result = listen_server->SetUp();

//     EXPECT_EQ(result, 1);

//     bool ret = model.AddFriend(std::to_string(i), friend_name, friend_ip, friend_port);

//     EXPECT_TRUE(ret);
//   }
  
//   auto connections = model.LoadConnections();

//   EXPECT_EQ(connections.size(), 4);

//   for (auto it = tmp.begin(); it != tmp.end(); ++it) {
//     it->second->TearDown();
//   }
// }

class FriendClientModelTest : public ::testing::Test {
 public:
  FriendClientModelTest() {
    name_one = "mitch";
    name_two = "micky";

    uuid_one = "test";
    uuid_two = "less";

    ip_one = "localhost-one";
    ip_two = "localhost-two";

    port_one = "1234";
    port_two = "5678";
  }

 protected:
  std::string name_one;
  std::string name_two;

  std::string uuid_one;
  std::string uuid_two;

  std::string ip_one;
  std::string ip_two;

  std::string port_one;
  std::string port_two;
};

TEST_F(FriendClientModelTest, AddFriendTrue) {
  ClientModel model;

  bool ret = model.AddFriend(uuid_one, name_one, ip_one, port_one);

  EXPECT_TRUE(ret);
}

TEST_F(FriendClientModelTest, AddFriendDoubleTrue) {
  ClientModel model;

  EXPECT_TRUE(model.AddFriend(uuid_one, name_one, ip_one, port_one));
  EXPECT_TRUE(model.AddFriend(uuid_two, name_two, ip_two, port_two));
}

TEST_F(FriendClientModelTest, AddFriendFalse) {
  ClientModel model;

  EXPECT_TRUE(model.AddFriend(uuid_one, name_one, ip_one, port_one));
  EXPECT_FALSE(model.AddFriend(uuid_one, name_one, ip_two, port_two));
}

TEST_F(FriendClientModelTest, AddFriendDoubleFalse) {
  ClientModel model;

  EXPECT_TRUE(model.AddFriend(uuid_one, name_one, ip_one, port_one));
  EXPECT_TRUE(model.AddFriend(uuid_two, name_two, ip_two, port_two));
  EXPECT_FALSE(model.AddFriend(uuid_one, name_one, ip_one, port_one));
  EXPECT_FALSE(model.AddFriend(uuid_two, name_two, ip_two, port_two));
}

TEST_F(FriendClientModelTest, AddFriendManyTrue) {
  ClientModel model;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(model.AddFriend(uuid, name_one, ip_one, port_one));
  }
}

TEST_F(FriendClientModelTest, AddFriendManyFalse) {
  ClientModel model;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(model.AddFriend(uuid, name_one, ip_one, port_one));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_FALSE(model.AddFriend(uuid, name_one, ip_one, port_one));
  }
}

TEST_F(FriendClientModelTest, GetFriendSingle) {
  ClientModel model;

  model.AddFriend(uuid_one, name_one, ip_one, port_one);
  std::shared_ptr<FriendNode> node_one = model.GetFriend(uuid_one);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
}

TEST_F(FriendClientModelTest, GetFriendDouble) {
  ClientModel model;

  model.AddFriend(uuid_one, name_one, ip_one, port_one);
  model.AddFriend(uuid_two, name_two, ip_two, port_two);

  std::shared_ptr<FriendNode> node_one = model.GetFriend(uuid_one);
  std::shared_ptr<FriendNode> node_two = model.GetFriend(uuid_two);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
  EXPECT_EQ(node_two->GetUuid(), uuid_two);
}

TEST_F(FriendClientModelTest, GetFriendMany) {
  ClientModel model;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(model.AddFriend(uuid, name_one, ip_one, port_one));
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

  EXPECT_TRUE(model.AddFriend(uuid_one, name_one, ip_one, port_one));
  EXPECT_TRUE(model.DeleteFriend(uuid_one));
}

TEST_F(FriendClientModelTest, DeleteFriendDouble) {
  ClientModel model;

  EXPECT_TRUE(model.AddFriend(uuid_one, name_one, ip_one, port_one));
  EXPECT_TRUE(model.DeleteFriend(uuid_one));

  EXPECT_TRUE(model.AddFriend(uuid_two, name_two, ip_two, port_two));
  EXPECT_TRUE(model.DeleteFriend(uuid_two));
}

TEST_F(FriendClientModelTest, DeleteFriendMany) {
  ClientModel model;

  for (int i = 0; i < 100; ++i) {
    EXPECT_TRUE(model.AddFriend(uuid_one, name_one, ip_one, port_one));
    EXPECT_TRUE(model.DeleteFriend(uuid_one));
  }
}

TEST_F(FriendClientModelTest, DeleteFriendError) {
  ClientModel model;

  EXPECT_FALSE(model.DeleteFriend(uuid_one));
}

TEST_F(FriendClientModelTest, AddDeleteDeleteFriendError) {
  ClientModel model;

  EXPECT_TRUE(model.AddFriend(uuid_one, name_two, ip_one, port_one));
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

    ip_one = "localhost-one";
    ip_two = "localhost-two";

    port_one = "1234";
    port_two = "5678";
  }

 protected:
  std::string name_one;
  std::string name_two;

  std::string uuid_one;
  std::string uuid_two;

  std::string owner_one;
  std::string owner_two;

  std::string ip_one;
  std::string ip_two;

  std::string port_one;
  std::string port_two;
};

TEST_F(ServerClientModelTest, AddServerTrue) {
  ClientModel model;

  bool ret = model.AddServer(uuid_one, name_one, owner_one, ip_one, port_one);

  EXPECT_TRUE(ret);
}

TEST_F(ServerClientModelTest, AddServerDoubleTrue) {
  ClientModel model;

  EXPECT_TRUE(model.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
  EXPECT_TRUE(model.AddServer(uuid_two, name_two, owner_two, ip_two, port_two));
}

TEST_F(ServerClientModelTest, AddServerFalse) {
  ClientModel model;

  EXPECT_TRUE(model.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
  EXPECT_FALSE(model.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
}

TEST_F(ServerClientModelTest, AddServerDoubleFalse) {
  ClientModel model;

  EXPECT_TRUE(model.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
  EXPECT_TRUE(model.AddServer(uuid_two, name_two, owner_two, ip_two, port_two));
  EXPECT_FALSE(model.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
  EXPECT_FALSE(model.AddServer(uuid_two, name_two, owner_two, ip_two, port_two));
}

TEST_F(ServerClientModelTest, AddServerManyTrue) {
  ClientModel model;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(model.AddServer(uuid, name_one, owner_one, ip_one, port_one));
  }
}

TEST_F(ServerClientModelTest, AddServerManyFalse) {
  ClientModel model;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(model.AddServer(uuid, name_one, owner_one, ip_one, port_one));
  }

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_FALSE(model.AddServer(uuid, name_one, owner_one, ip_one, port_one));
  }
}

TEST_F(ServerClientModelTest, GetServerSingle) {
  ClientModel model;

  model.AddServer(uuid_one, name_one, owner_one, ip_one, port_one);
  std::shared_ptr<ServerNode> node_one = model.GetServer(uuid_one);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
}

TEST_F(ServerClientModelTest, GetServerDouble) {
  ClientModel model;

  model.AddServer(uuid_one, name_one, owner_one, ip_one, port_one);
  model.AddServer(uuid_two, name_two, owner_two, ip_two, port_two);

  std::shared_ptr<ServerNode> node_one = model.GetServer(uuid_one);
  std::shared_ptr<ServerNode> node_two = model.GetServer(uuid_two);

  EXPECT_EQ(node_one->GetUuid(), uuid_one);
  EXPECT_EQ(node_two->GetUuid(), uuid_two);
}

TEST_F(ServerClientModelTest, GetServerMany) {
  ClientModel model;

  for (int index = 0; index < 100; index++) {
    std::string uuid = std::to_string(index);
    EXPECT_TRUE(model.AddServer(uuid, name_one, owner_one, ip_one, port_one));
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

  EXPECT_TRUE(model.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
  EXPECT_TRUE(model.DeleteServer(uuid_one));
}

TEST_F(ServerClientModelTest, DeleteServerDouble) {
  ClientModel model;

  EXPECT_TRUE(model.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
  EXPECT_TRUE(model.DeleteServer(uuid_one));

  EXPECT_TRUE(model.AddServer(uuid_two, name_two, owner_two, ip_two, port_two));
  EXPECT_TRUE(model.DeleteServer(uuid_two));
}

TEST_F(ServerClientModelTest, DeleteServerMany) {
  ClientModel model;

  for (int i = 0; i < 100; ++i) {
    EXPECT_TRUE(model.AddServer(uuid_one, name_one, owner_one, ip_one, port_one));
    EXPECT_TRUE(model.DeleteServer(uuid_one));
  }
}

TEST_F(ServerClientModelTest, DeleteServerError) {
  ClientModel model;

  EXPECT_FALSE(model.DeleteServer(uuid_one));
}

TEST_F(ServerClientModelTest, AddDeleteDeleteServerError) {
  ClientModel model;

  EXPECT_TRUE(model.AddServer(uuid_one, name_two, owner_one, ip_one, port_one));
  EXPECT_TRUE(model.DeleteServer(uuid_one));
  EXPECT_FALSE(model.DeleteServer(uuid_one));
}