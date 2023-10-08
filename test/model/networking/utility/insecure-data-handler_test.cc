#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "model/networking/utility/insecure-data-handler.h"

class InsecureDataHandlerTest : public ::testing::Test {
 protected:
  model::InsecureDataHandler data_handler;
  
  std::string data;
  
  std::string packet_correct;
  
  void SetUp() override {
    data = "this is test data";

    packet_correct = R"({"payload":"this is test data"})";
  }

  void TearDown() override {
  }
};

TEST_F(InsecureDataHandlerTest, FormatSendTest) {
  std::string packet = data_handler.FormatSend(data);

  EXPECT_STREQ(packet_correct.c_str(), packet.c_str());
}

TEST_F(InsecureDataHandlerTest, FormatReadTest) {
  std::string payload = data_handler.FormatRead(packet_correct);
  
  EXPECT_STREQ(data.c_str(), payload.c_str());
}

TEST_F(InsecureDataHandlerTest, FormatSendThenReadTest) {
  std::string packet = data_handler.FormatSend(data);

  EXPECT_STREQ(packet_correct.c_str(), packet.c_str());

  std::string payload = data_handler.FormatRead(packet);

  EXPECT_STREQ(data.c_str(), payload.c_str());
}