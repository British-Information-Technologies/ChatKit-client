#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <sodium.h>

#include "model/networking/utility/secure-data-handler.h"

#define SUCCESS 0

class SecureDataHandlerTest : public ::testing::Test {
  protected:
    model::SecureDataHandler *data_handler_A;
    model::SecureDataHandler *data_handler_B;
    
    std::string data;

    unsigned char public_key_A[crypto_kx_PUBLICKEYBYTES];
    unsigned char secret_key_A[crypto_kx_SECRETKEYBYTES];
    
    unsigned char public_key_B[crypto_kx_PUBLICKEYBYTES];
    unsigned char secret_key_B[crypto_kx_SECRETKEYBYTES];
    
    unsigned char session_key_rx_A[crypto_kx_SESSIONKEYBYTES];
    unsigned char session_key_tx_A[crypto_kx_SESSIONKEYBYTES];
    
    unsigned char session_key_rx_B[crypto_kx_SESSIONKEYBYTES];
    unsigned char session_key_tx_B[crypto_kx_SESSIONKEYBYTES];

    void SetUp() override {      
      if(crypto_kx_keypair(public_key_A, secret_key_A)) return;
      
      if(crypto_kx_keypair(public_key_B, secret_key_B)) return;
      
      if(crypto_kx_client_session_keys(
        session_key_rx_A,
        session_key_tx_A,
        public_key_A,
        secret_key_A,
        public_key_B
      )) {
        return;
      }
   
      if(crypto_kx_server_session_keys(
        session_key_rx_B,
        session_key_tx_B,
        public_key_B,
        secret_key_B,
        public_key_A
      )) {
        return;
      }

      for (int i = 0; i < crypto_kx_SESSIONKEYBYTES; ++i) EXPECT_EQ(session_key_rx_A[i], session_key_tx_B[i]);

      for (int i = 0; i < crypto_kx_SESSIONKEYBYTES; ++i) EXPECT_EQ(session_key_tx_A[i], session_key_rx_B[i]);

      data_handler_A = new model::SecureDataHandler(session_key_rx_A, session_key_tx_A);
      
      data_handler_B = new model::SecureDataHandler(session_key_rx_B, session_key_tx_B);

      data = "this is test data";
    }

    void TearDown() override {
      free(data_handler_A);
    }
};

TEST_F(SecureDataHandlerTest, FormatSendTest) { 
  std::string packet = data_handler_A->FormatSend(data);

  std::cout << "data: " << data << std::endl;
  std::cout << "packet: " << packet << std::endl;

  EXPECT_STRNE(data.c_str(), packet.c_str());
}

TEST_F(SecureDataHandlerTest, FormatSendThenReadTest) {
  // Alice - Send
  std::string packet = data_handler_A->FormatSend(data);

  std::cout << "data: " << data << std::endl;
  std::cout << "packet: " << packet << std::endl;

  EXPECT_STRNE(data.c_str(), packet.c_str());

  // Bob - Read
  std::string payload = data_handler_B->FormatRead(packet);

  std::cout << "original data: " << payload << std::endl;
  
  EXPECT_STREQ(data.c_str(), payload.c_str());
  EXPECT_EQ(data.length(), payload.length());
}