#include "model/networking/utility/elliptic-curve-diffiehellman.h"

#include <gtest/gtest.h>

using namespace networking_utility;

TEST(EllipticCurveDiffieHellmanTest, CreateKeyPair) {
  EVP_PKEY_free_ptr alice_private_key = GenerateKeyPair();
  EXPECT_NE(alice_private_key, nullptr);
}

TEST(EllipticCurveDiffieHellmanTest, ExtractPublicKeyFromPrivateKey) {
  EVP_PKEY_free_ptr alice_private_key = GenerateKeyPair();
  EVP_PKEY_free_ptr alice_public_key =
      ExtractPublicKey(alice_private_key.get());

  EXPECT_NE(alice_private_key, nullptr);
  EXPECT_NE(alice_public_key, nullptr);
}

TEST(EllipticCurveDiffieHellmanTest, GenerateDifferentKeyPairs) {
  EVP_PKEY_free_ptr alice_private_key = GenerateKeyPair();
  EVP_PKEY_free_ptr bob_private_key = GenerateKeyPair();

  EXPECT_NE(alice_private_key.get(), bob_private_key.get());
}

TEST(EllipticCurveDiffieHellmanTest, ExtractDifferentPublicKeys) {
  EVP_PKEY_free_ptr alice_private_key = GenerateKeyPair();
  EVP_PKEY_free_ptr bob_private_key = GenerateKeyPair();

  EXPECT_NE(alice_private_key, nullptr);
  EXPECT_NE(bob_private_key, nullptr);

  EVP_PKEY_free_ptr alice_public_key =
      ExtractPublicKey(alice_private_key.get());
  EVP_PKEY_free_ptr bob_public_key = ExtractPublicKey(bob_private_key.get());

  EXPECT_NE(alice_public_key, nullptr);
  EXPECT_NE(bob_public_key, nullptr);
}

TEST(EllipticCurveDiffieHellmanTest, CreateSharedSecret) {
  EVP_PKEY_free_ptr alice_private_key = GenerateKeyPair();
  EVP_PKEY_free_ptr bob_private_key = GenerateKeyPair();

  EXPECT_NE(alice_private_key, nullptr);
  EXPECT_NE(bob_private_key, nullptr);

  EVP_PKEY_free_ptr alice_public_key =
      ExtractPublicKey(alice_private_key.get());
  EVP_PKEY_free_ptr bob_public_key = ExtractPublicKey(bob_private_key.get());

  EXPECT_NE(alice_public_key, nullptr);
  EXPECT_NE(bob_public_key, nullptr);

  DerivedData* secret_alice =
      DeriveSharedSecret(bob_public_key.get(), alice_private_key.get());
  DerivedData* secret_bob =
      DeriveSharedSecret(alice_public_key.get(), bob_private_key.get());

  // turn shared secret into a displayable format
  BIGNUM* secret_alice_BN = BN_new();
  BIGNUM* secret_bob_BN = BN_new();

  BN_bin2bn(secret_alice->secret, secret_alice->length, secret_alice_BN);
  BN_bin2bn(secret_bob->secret, secret_bob->length, secret_bob_BN);

  std::cout << "Secret computed by Alice: ";
  BN_print_fp(stdout, secret_alice_BN);
  std::cout << std::endl;

  std::cout << "Secret computed by Bob: ";
  BN_print_fp(stdout, secret_bob_BN);
  std::cout << std::endl;

  EXPECT_EQ(*secret_alice->secret, *secret_bob->secret);

  BN_free(secret_alice_BN);
  BN_free(secret_bob_BN);
}
