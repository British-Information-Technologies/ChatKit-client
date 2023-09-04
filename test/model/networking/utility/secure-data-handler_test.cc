#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "model/networking/utility/secure-data-handler.h"

class SecureDataHandlerTest : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }

  protected:
    unsigned char fake_secret[20] = "fake_shared_secret\0";
};

TEST_F(SecureDataHandlerTest, FormatSendTest) {
  model::SecureDataHandler data_handler(fake_secret);

  std::string data("this is test data");

  std::string packet = data_handler.FormatSend(data);

  std::cout << "data: " << data << std::endl;
  std::cout << "packet: " << packet << std::endl;

  EXPECT_STRNE(data.c_str(), packet.c_str());
}

TEST_F(SecureDataHandlerTest, FormatSendThenReadTest) {
  model::SecureDataHandler data_handler(fake_secret);

  std::string data("this is test data");

  std::string packet = data_handler.FormatSend(data);

  std::cout << "data: " << data << std::endl;
  std::cout << "packet: " << packet << std::endl;

  EXPECT_STRNE(data.c_str(), packet.c_str());

  std::string payload = data_handler.FormatRead(packet);
  
  EXPECT_STREQ(data.c_str(), payload.c_str());
}