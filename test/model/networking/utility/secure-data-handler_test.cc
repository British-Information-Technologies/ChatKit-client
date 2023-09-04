#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "model/networking/utility/secure-data-handler.h"

class SecureDataHandlerTest : public ::testing::Test {
  protected:
    model::SecureDataHandler *data_handler;
    
    std::string data;

    void SetUp() override {
      unsigned char *fake_secret = (unsigned char*) malloc(sizeof(unsigned char) * 20);
      fake_secret = (unsigned char*)"fake_shared_secret\0";
  
      data_handler = new model::SecureDataHandler(fake_secret);

      data = "this is test data";
    }

    void TearDown() override {
      free(data_handler);
    }
};

TEST_F(SecureDataHandlerTest, FormatSendTest) { 
  std::string packet = data_handler->FormatSend(data);

  std::cout << "data: " << data << std::endl;
  std::cout << "packet: " << packet << std::endl;

  EXPECT_STRNE(data.c_str(), packet.c_str());
}

TEST_F(SecureDataHandlerTest, FormatSendThenReadTest) {
  std::string packet = data_handler->FormatSend(data);

  std::cout << "data: " << data << std::endl;
  std::cout << "packet: " << packet << std::endl;

  EXPECT_STRNE(data.c_str(), packet.c_str());

  std::string payload = data_handler->FormatRead(packet);

  std::cout << "original data: " << payload << std::endl;
  
  EXPECT_STREQ(data.c_str(), payload.c_str());
  EXPECT_EQ(data.length(), payload.length());
}