#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <sodium.h>

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

TEST_F(EncodeDecodeTest, DecodePublicKeyTest) {
    unsigned char public_key[crypto_kx_PUBLICKEYBYTES];
    unsigned char secret_key[crypto_kx_SECRETKEYBYTES];
    
    if(crypto_kx_keypair(public_key, secret_key)) return;
    
    std::string data_encoded = model::Bin2Base64(public_key, crypto_kx_PUBLICKEYBYTES);
    
    EXPECT_NE(crypto_kx_PUBLICKEYBYTES, data_encoded.length());
    
    auto [data_original, data_original_len] = model::Base642Bin(data_encoded);
    
    EXPECT_EQ(crypto_kx_PUBLICKEYBYTES, data_original_len);

    for (int i = 0; i < crypto_kx_PUBLICKEYBYTES; ++i) EXPECT_EQ(public_key[i], data_original[i]);
    
    free(data_original);
}