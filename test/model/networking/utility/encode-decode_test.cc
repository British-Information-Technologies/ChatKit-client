#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "model/networking/utility/encode.h"
#include "model/networking/utility/decode.h"

class EncodeDecodeTest : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

TEST_F(EncodeDecodeTest, EncodeDataTest) {
    unsigned char data[] = "This is my encode test";
    
    std::string data_encoded = model::Bin2Base64(data, 22);
    
    std::cout << "Data: " << data << std::endl;
    std::cout << "Encoded Data: " << data_encoded << std::endl;
    
    char data_str[sizeof(data)];
    strcpy(data_str, (char*) data);
    
    EXPECT_STRNE(data_str, data_encoded.c_str());
}

TEST_F(EncodeDecodeTest, DecodeDataTest) {
    unsigned char data[] = "This is my encode test";
    
    std::string data_encoded = model::Bin2Base64(data, 22);
    
    std::cout << "Data: " << data << std::endl;
    std::cout << "Encoded Data: " << data_encoded << std::endl;

    char data_str[sizeof(data)];
    strcpy(data_str, (char*) data);
    
    EXPECT_STRNE(data_str, data_encoded.c_str());
    
    auto [data_original, data_original_len] = model::Base642Bin(data_encoded);
    
    std::cout << "Original Data: " << data_original << "(" << data_original_len << ")" << std::endl;
    
    EXPECT_STREQ((char*) data, (char*) data_original);
    
    free(data_original);
}
