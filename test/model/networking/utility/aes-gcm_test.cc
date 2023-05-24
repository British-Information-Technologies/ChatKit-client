#include "model/networking/utility/aes-gcm.h"

#include <gtest/gtest.h>
#include <openssl/evp.h>

using namespace model_networking_utility;

class AESGCMTest : public ::testing::Test {
 public:
  AESGCMTest() {
    this->key.secret =
        (unsigned char *)"300EE3B4C88D252280F8972B42EC4605A0499DE55248EC17D08F5CB8AC080B17";
    this->key.length = 64;
  }

 protected:
  DerivedData key;

  std::string additional = "The five boxing wizards jump quickly.";

  byte *iv = (unsigned char *)"0123456789012345";
  size_t iv_len = 16;
};

TEST_F(AESGCMTest, SingleEncryptMatchKeyLength) {
  std::string plaintext =
      "hey mitch how are you today. This is pretty crazy wild bam bam !";
  std::string ciphertext;
  byte tag[17];
  tag[16] = '\0';

  int ciphertext_len =
      AesGcmEncrypt(plaintext, additional, &key, iv, iv_len, ciphertext, tag);

  std::cout << "Ciphertext: ";
  BIO_dump_fp(stdout, (const char *)&ciphertext[0], ciphertext.size());
  std::cout << std::endl;

  std::cout << "Tag: ";
  BIO_dump_fp(stdout, (const char *)tag, 16);
  std::cout << std::endl;

  EXPECT_EQ(plaintext.size(), ciphertext.size());
  EXPECT_EQ(ciphertext.size(), ciphertext_len);

  std::cout << "Ciphertext: " << ciphertext << std::endl;
  std::cout << "plaintext : " << plaintext << std::endl;

  EXPECT_NE(plaintext, ciphertext);
}

TEST_F(AESGCMTest, EncryptDecryptMatchKeyLength) {
  std::string plaintext =
      "hey mitch how are you today. This is pretty crazy wild bam bam !";
  std::string ciphertext;
  std::string decryptedtext;
  byte tag[17];
  tag[16] = '\0';

  int ciphertext_len =
      AesGcmEncrypt(plaintext, additional, &key, iv, iv_len, ciphertext, tag);

  std::cout << "Ciphertext: ";
  BIO_dump_fp(stdout, (const char *)&ciphertext[0], ciphertext.size());
  std::cout << std::endl;

  std::cout << "Tag: ";
  BIO_dump_fp(stdout, (const char *)tag, 16);
  std::cout << std::endl;

  EXPECT_EQ(plaintext.size(), ciphertext.size());
  EXPECT_EQ(ciphertext.size(), ciphertext_len);
  EXPECT_NE(plaintext, ciphertext);

  std::cout << "encrypted: " << ciphertext << std::endl;

  int decryptedtext_len = AesGcmDecrypt(ciphertext, ciphertext_len, additional,
                                        tag, &key, iv, iv_len, decryptedtext);

  std::cout << "decrypted: " << decryptedtext << std::endl;
  std::cout << "plaintext: " << plaintext << std::endl;

  EXPECT_EQ(decryptedtext_len, plaintext.size());
  EXPECT_EQ(decryptedtext.size(), plaintext.size());
  EXPECT_EQ(decryptedtext, plaintext);
}

TEST_F(AESGCMTest, EncryptShortKeyLength) {
  std::string plaintext = "hey mitch how are you today.";
  std::string ciphertext;
  byte tag[17];
  tag[16] = '\0';

  int ciphertext_len =
      AesGcmEncrypt(plaintext, additional, &key, iv, iv_len, ciphertext, tag);

  std::cout << "Ciphertext: ";
  BIO_dump_fp(stdout, (const char *)&ciphertext[0], ciphertext.size());
  std::cout << std::endl;

  std::cout << "Tag: ";
  BIO_dump_fp(stdout, (const char *)tag, 16);
  std::cout << std::endl;

  EXPECT_EQ(plaintext.size(), ciphertext.size());
  EXPECT_EQ(ciphertext.size(), ciphertext_len);
  EXPECT_NE(plaintext, ciphertext);
}

TEST_F(AESGCMTest, EncryptDecryptShortKeyLength) {
  std::string plaintext = "hey mitch how are you today.";
  std::string ciphertext;
  std::string decryptedtext;
  byte tag[17];
  tag[16] = '\0';

  int ciphertext_len =
      AesGcmEncrypt(plaintext, additional, &key, iv, iv_len, ciphertext, tag);

  std::cout << "Ciphertext: ";
  BIO_dump_fp(stdout, (const char *)&ciphertext[0], ciphertext.size());
  std::cout << std::endl;

  std::cout << "Tag: ";
  BIO_dump_fp(stdout, (const char *)tag, 16);
  std::cout << std::endl;

  EXPECT_EQ(plaintext.size(), ciphertext.size());
  EXPECT_EQ(ciphertext.size(), ciphertext_len);
  EXPECT_NE(plaintext, ciphertext);

  std::cout << "encrypted: " << ciphertext << std::endl;

  int decryptedtext_len = AesGcmDecrypt(ciphertext, ciphertext_len, additional,
                                        tag, &key, iv, iv_len, decryptedtext);

  std::cout << "decrypted: " << decryptedtext << std::endl;
  std::cout << "plaintext: " << plaintext << std::endl;

  EXPECT_EQ(decryptedtext_len, plaintext.size());
  EXPECT_EQ(decryptedtext.size(), plaintext.size());
  EXPECT_EQ(decryptedtext, plaintext);
}

TEST_F(AESGCMTest, EncryptLongKeyLength) {
  std::string plaintext =
      "hey mitch how are you today. epic bam dam wam smash bash ropyras help "
      "me please i beg you i need help ahahhaha!";
  std::string ciphertext;
  byte tag[17];
  tag[16] = '\0';

  int ciphertext_len =
      AesGcmEncrypt(plaintext, additional, &key, iv, iv_len, ciphertext, tag);

  std::cout << "Ciphertext: ";
  BIO_dump_fp(stdout, (const char *)&ciphertext[0], ciphertext.size());
  std::cout << std::endl;

  std::cout << "Tag: ";
  BIO_dump_fp(stdout, (const char *)tag, 16);
  std::cout << std::endl;

  EXPECT_EQ(plaintext.size(), ciphertext.size());
  EXPECT_EQ(ciphertext.size(), ciphertext_len);
  EXPECT_NE(plaintext, ciphertext);
}

TEST_F(AESGCMTest, EncryptDecryptLongKeyLength) {
  std::string plaintext =
      "hey mitch how are you today. epic bam dam wam smash bash ropyras help "
      "me please i beg you i need help ahahahahaha!";
  std::string ciphertext;
  std::string decryptedtext;
  byte tag[17];
  tag[16] = '\0';

  int ciphertext_len =
      AesGcmEncrypt(plaintext, additional, &key, iv, iv_len, ciphertext, tag);

  std::cout << "Ciphertext: ";
  BIO_dump_fp(stdout, (const char *)&ciphertext[0], ciphertext.size());
  std::cout << std::endl;

  std::cout << "Tag: ";
  BIO_dump_fp(stdout, (const char *)tag, 16);
  std::cout << std::endl;

  EXPECT_EQ(plaintext.size(), ciphertext.size());
  EXPECT_EQ(ciphertext.size(), ciphertext_len);
  EXPECT_NE(plaintext, ciphertext);

  std::cout << "encrypted: " << ciphertext << std::endl;

  int decryptedtext_len = AesGcmDecrypt(ciphertext, ciphertext_len, additional,
                                        tag, &key, iv, iv_len, decryptedtext);

  std::cout << "decrypted: " << decryptedtext << std::endl;
  std::cout << "plaintext: " << plaintext << std::endl;

  EXPECT_EQ(decryptedtext_len, plaintext.size());
  EXPECT_EQ(decryptedtext.size(), plaintext.size());
  EXPECT_EQ(decryptedtext, plaintext);
}

TEST_F(AESGCMTest, EncryptDecryptManyMessages) {
  std::string plaintext = "hey mitch how are you today.";
  std::string ciphertext;
  std::string decryptedtext;
  byte tag[17];
  tag[16] = '\0';

  for (int i = 0; i < 250; ++i) {
    int ciphertext_len =
        AesGcmEncrypt(plaintext, additional, &key, iv, iv_len, ciphertext, tag);

    std::cout << "Ciphertext: ";
    BIO_dump_fp(stdout, (const char *)&ciphertext[0], ciphertext.size());
    std::cout << std::endl;

    std::cout << "Tag: ";
    BIO_dump_fp(stdout, (const char *)tag, 16);
    std::cout << std::endl;

    EXPECT_EQ(plaintext.size(), ciphertext.size());
    EXPECT_EQ(ciphertext.size(), ciphertext_len);
    EXPECT_NE(plaintext, ciphertext);

    std::cout << "encrypted: " << ciphertext << std::endl;

    int decryptedtext_len =
        AesGcmDecrypt(ciphertext, ciphertext_len, additional, tag, &key, iv,
                      iv_len, decryptedtext);

    std::cout << "decrypted: " << decryptedtext << std::endl;
    std::cout << "plaintext: " << plaintext << std::endl;

    EXPECT_EQ(decryptedtext_len, plaintext.size());
    EXPECT_EQ(decryptedtext.size(), plaintext.size());
    EXPECT_EQ(decryptedtext, plaintext);
  }
}