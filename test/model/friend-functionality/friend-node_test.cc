#include "model/friend-functionality/friend-node.h"

#include <gtest/gtest.h>

#include <iostream>
#include <string>

using namespace model_friend_functionality;

class FriendNodeTest : public ::testing::Test {
 public:
  FriendNodeTest() {
    name_one = "mitch";
    name_two = "micky";

    uuid_one = "testtesttest1234567890";
    uuid_two = "testtest1234567890";

    ip_one = "localhost";
    ip_two = "localhost-nope";

    port_one = "1234";
    port_two = "5678";

    friend_one = new FriendNode(uuid_one, name_one, ip_one, port_one);
    friend_two = new FriendNode(uuid_two, name_two, ip_two, port_two);
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
  FriendNode tmp_friend(uuid, name, ip_one, port_one);

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
    friends_array[index] = new FriendNode(uuid, name, ip_one, port_one);
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
  FriendNode *tmp_friend = new FriendNode(uuid, name, ip_one, port_one);

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
  FriendNode tmp_friend(uuid, name, ip_one, port_one);

  EXPECT_EQ(tmp_friend.GetUuid(), uuid);

  uuid = "12";
  EXPECT_NE(tmp_friend.GetUuid(), uuid);

  uuid = "1234";
  EXPECT_EQ(tmp_friend.GetUuid(), uuid);
}

TEST_F(FriendNodeTest, GetUuidMany) {
  FriendNode *friends_array[20];
  std::string name = "mitch";

  for (int index = 0; index < 20; ++index) {
    std::string uuid = std::to_string(index);
    friends_array[index] = new FriendNode(uuid, name, ip_one, port_one);
  }

  for (int index = 0; index < 20; ++index) {
    EXPECT_EQ(friends_array[index]->GetUuid(), std::to_string(index));
  }
}

TEST_F(FriendNodeTest, GetUuidNotEqual) {
  EXPECT_NE(friend_one->GetUuid(), friend_two->GetUuid());
}

TEST_F(FriendNodeTest, GetUuidEqual) {
  std::string name = "jeff";
  std::string uuid = "testtesttest1234567890";
  FriendNode *tmp_friend = new FriendNode(uuid, name, ip_one, port_one);

  EXPECT_EQ(friend_one->GetUuid(), tmp_friend->GetUuid());
}

TEST_F(FriendNodeTest, GetIp) {
  std::string ip = "localhost";
  EXPECT_EQ(friend_one->GetIp(), ip);
}

TEST_F(FriendNodeTest, GetIpDouble) {
  EXPECT_EQ(friend_one->GetIp(), ip_one);
  EXPECT_EQ(friend_two->GetIp(), ip_two);
}

TEST_F(FriendNodeTest, GetIpConstant) {
  std::string name = "mitch";
  std::string uuid = "1234";
  std::string ip = "localhost";
  FriendNode tmp_friend(uuid, name, ip, port_one);

  EXPECT_EQ(tmp_friend.GetIp(), ip);

  ip = "12";
  EXPECT_NE(tmp_friend.GetIp(), ip);

  ip = "localhost";
  EXPECT_EQ(tmp_friend.GetIp(), ip);
}

TEST_F(FriendNodeTest, GetIpMany) {
  FriendNode *friends_array[20];
  std::string name = "mitch";

  for (int index = 0; index < 20; ++index) {
    std::string ip = std::to_string(index);
    friends_array[index] = new FriendNode(ip, name, ip, port_one);
  }

  for (int index = 0; index < 20; ++index) {
    EXPECT_EQ(friends_array[index]->GetIp(), std::to_string(index));
  }
}

TEST_F(FriendNodeTest, GetIpNotEqual) {
  EXPECT_NE(friend_one->GetIp(), friend_two->GetIp());
}

TEST_F(FriendNodeTest, GetIpEqual) {
  std::string name = "jeff";
  std::string uuid = "testtesttest1234567890";
  std::string ip = "localhost";

  FriendNode *tmp_friend = new FriendNode(uuid, name, ip, port_one);

  EXPECT_EQ(friend_one->GetIp(), tmp_friend->GetIp());
}

TEST_F(FriendNodeTest, GetPort) {
  std::string port = "1234";
  EXPECT_EQ(friend_one->GetPort(), port);
}

TEST_F(FriendNodeTest, GetPortDouble) {
  EXPECT_EQ(friend_one->GetPort(), port_one);
  EXPECT_EQ(friend_two->GetPort(), port_two);
}

TEST_F(FriendNodeTest, GetPortConstant) {
  std::string name = "mitch";
  std::string uuid = "1234";
  std::string ip = "localhost";
  std::string port = "1234";

  FriendNode tmp_friend(uuid, name, ip, port);

  EXPECT_EQ(tmp_friend.GetPort(), port);

  port = "12";
  EXPECT_NE(tmp_friend.GetPort(), port);

  ip = "1234";
  EXPECT_EQ(tmp_friend.GetPort(), port);
}

TEST_F(FriendNodeTest, GetPortMany) {
  FriendNode *friends_array[20];
  std::string name = "mitch";

  for (int index = 0; index < 20; ++index) {
    std::string port = std::to_string(index);
    friends_array[index] = new FriendNode(port, name, ip_one, port);
  }

  for (int index = 0; index < 20; ++index) {
    EXPECT_EQ(friends_array[index]->GetPort(), std::to_string(index));
  }
}

TEST_F(FriendNodeTest, GetPortNotEqual) {
  EXPECT_NE(friend_one->GetPort(), friend_two->GetPort());
}

TEST_F(FriendNodeTest, GetPortEqual) {
  std::string name = "jeff";
  std::string uuid = "testtesttest1234567890";
  std::string ip = "localhost";
  std::string port = "1234";

  FriendNode *tmp_friend = new FriendNode(uuid, name, ip, port);

  EXPECT_EQ(friend_one->GetPort(), tmp_friend->GetPort());
}