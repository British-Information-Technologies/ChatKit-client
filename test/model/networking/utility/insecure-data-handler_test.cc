#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "model/networking/utility/insecure-data-handler.h"

class InsecureDataHandlerTest : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

TEST_F(InsecureDataHandlerTest, FormatSendTest) {
  model::InsecureDataHandler data_handler;

  std::string data("this is test data");

  std::string packet = data_handler.FormatSend(data);

  std::string packet_correct(R"({"payload":"this is test data"})");

  EXPECT_STREQ(packet_correct.c_str(), packet.c_str());
}

TEST_F(InsecureDataHandlerTest, FormatReadTest) {
  model::InsecureDataHandler data_handler;

  std::string packet(R"({"payload":"this is test data"})");

  std::string payload = data_handler.FormatRead(packet);
  
  std::string data("this is test data");
  
  EXPECT_STREQ(data.c_str(), payload.c_str());
}

TEST_F(InsecureDataHandlerTest, FormatSendThenReadTest) {
  model::InsecureDataHandler data_handler;

  std::string data("this is test data");

  std::string packet = data_handler.FormatSend(data);

  std::string packet_correct(R"({"payload":"this is test data"})");

  EXPECT_STREQ(packet_correct.c_str(), packet.c_str());

  std::string payload = data_handler.FormatRead(packet);

  EXPECT_STREQ(data.c_str(), payload.c_str());
}