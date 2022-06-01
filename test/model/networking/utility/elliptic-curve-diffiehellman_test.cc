#include "model/networking/utility/elliptic-curve-diffiehellman.h"

#include <gtest/gtest.h>
#include <openssl/pem.h>

using namespace model_networking_utility;

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

TEST(EllipticCurveDiffieHellmanTest, SerializeKey) {
  EVP_PKEY_free_ptr alice_private_key = GenerateKeyPair();
  EVP_PKEY_free_ptr alice_public_key =
      ExtractPublicKey(alice_private_key.get());

  std::string key = SerializePublicKey(alice_public_key.get());

  std::cout << key << std::endl;
}

TEST(EllipticCurveDiffieHellmanTest, SerializeDeserializeKey) {
  EVP_PKEY_free_ptr alice_private_key = GenerateKeyPair();
  EVP_PKEY_free_ptr alice_public_key =
      ExtractPublicKey(alice_private_key.get());

  std::string key = SerializePublicKey(alice_public_key.get());

  std::cout << "json: " << key << std::endl;

  EVP_PKEY_free_ptr public_key = DeserializePublicKey(key.c_str());

  /* Output keys in readable format */
  std::string key_one = SerializePublicKey(alice_public_key.get());
  std::string key_two = SerializePublicKey(public_key.get());
  std::cout << "key one: " << key_one << std::endl;
  std::cout << "key two: " << key_two << std::endl;

  EXPECT_EQ(key_one, key_two);
  EXPECT_EQ(key_one, key);
  EXPECT_EQ(key_two, key);
}

TEST(EllipticCurveDiffieHellmanTest, DeriveMatchingSecret) {
  EVP_PKEY_free_ptr alice_private_key = GenerateKeyPair();
  EVP_PKEY_free_ptr bob_private_key = GenerateKeyPair();

  EXPECT_NE(alice_private_key, nullptr);
  EXPECT_NE(bob_private_key, nullptr);

  EVP_PKEY_free_ptr alice_public_key =
      ExtractPublicKey(alice_private_key.get());
  EVP_PKEY_free_ptr bob_public_key = ExtractPublicKey(bob_private_key.get());

  EXPECT_NE(alice_public_key, nullptr);
  EXPECT_NE(bob_public_key, nullptr);

  std::string alice_key = SerializePublicKey(alice_public_key.get());
  std::cout << "alice: " << alice_key << std::endl;

  std::string bob_key = SerializePublicKey(bob_public_key.get());
  std::cout << "bob: " << bob_key << std::endl;

  EXPECT_NE(bob_key, alice_key);

  EVP_PKEY_free_ptr alice_peer_key = DeserializePublicKey(bob_key.c_str());
  EVP_PKEY_free_ptr bob_peer_key = DeserializePublicKey(alice_key.c_str());

  DerivedData* secret_alice =
      DeriveSharedSecret(alice_peer_key.get(), alice_private_key.get());
  DerivedData* secret_bob =
      DeriveSharedSecret(bob_peer_key.get(), bob_private_key.get());

  std::cout << "alice secret: " << *(secret_alice->secret) << std::endl;
  std::cout << "bob secret: " << *(secret_bob->secret) << std::endl;
  std::cout << "alice secret length: " << secret_alice->length << std::endl;
  std::cout << "bob secret length: " << secret_bob->length << std::endl;

  EXPECT_EQ(*(secret_alice->secret), *(secret_bob->secret));
  EXPECT_EQ(secret_alice->length, secret_bob->length);
}

TEST(EllipticCurveDiffieHellmanTest, DeriveMatchingSecretDouble) {
  EVP_PKEY_free_ptr alice_private_key = GenerateKeyPair();
  EVP_PKEY_free_ptr bob_private_key = GenerateKeyPair();

  EXPECT_NE(alice_private_key, nullptr);
  EXPECT_NE(bob_private_key, nullptr);

  EVP_PKEY_free_ptr alice_public_key =
      ExtractPublicKey(alice_private_key.get());
  EVP_PKEY_free_ptr bob_public_key = ExtractPublicKey(bob_private_key.get());

  EXPECT_NE(alice_public_key, nullptr);
  EXPECT_NE(bob_public_key, nullptr);

  std::string alice_key = SerializePublicKey(alice_public_key.get());
  std::cout << "alice: " << alice_key << std::endl;

  std::string bob_key = SerializePublicKey(bob_public_key.get());
  std::cout << "bob: " << bob_key << std::endl;

  EXPECT_NE(bob_key, alice_key);

  EVP_PKEY_free_ptr alice_peer_key = DeserializePublicKey(bob_key.c_str());
  EVP_PKEY_free_ptr bob_peer_key = DeserializePublicKey(alice_key.c_str());

  DerivedData* secret_alice =
      DeriveSharedSecret(alice_peer_key.get(), alice_private_key.get());
  DerivedData* secret_bob =
      DeriveSharedSecret(bob_peer_key.get(), bob_private_key.get());

  std::cout << "alice secret: " << *(secret_alice->secret) << std::endl;
  std::cout << "bob secret: " << *(secret_bob->secret) << std::endl;
  std::cout << "alice secret length: " << secret_alice->length << std::endl;
  std::cout << "bob secret length: " << secret_bob->length << std::endl;

  EXPECT_EQ(*(secret_alice->secret), *(secret_bob->secret));
  EXPECT_EQ(secret_alice->length, secret_bob->length);

  alice_key = SerializePublicKey(alice_public_key.get());
  std::cout << "alice: " << alice_key << std::endl;

  bob_key = SerializePublicKey(bob_public_key.get());
  std::cout << "bob: " << bob_key << std::endl;

  EXPECT_NE(bob_key, alice_key);

  alice_peer_key = DeserializePublicKey(bob_key.c_str());
  bob_peer_key = DeserializePublicKey(alice_key.c_str());

  secret_alice =
      DeriveSharedSecret(alice_peer_key.get(), alice_private_key.get());
  secret_bob = DeriveSharedSecret(bob_peer_key.get(), bob_private_key.get());

  std::cout << "alice secret: " << *(secret_alice->secret) << std::endl;
  std::cout << "bob secret: " << *(secret_bob->secret) << std::endl;
  std::cout << "alice secret length: " << secret_alice->length << std::endl;
  std::cout << "bob secret length: " << secret_bob->length << std::endl;

  EXPECT_EQ(*(secret_alice->secret), *(secret_bob->secret));
  EXPECT_EQ(secret_alice->length, secret_bob->length);
}

TEST(EllipticCurveDiffieHellmanTest, DeriveMatchingSecretMany) {
  for (int i = 0; i < 100; ++i) {
    EVP_PKEY_free_ptr alice_private_key = GenerateKeyPair();
    EVP_PKEY_free_ptr bob_private_key = GenerateKeyPair();

    EXPECT_NE(alice_private_key, nullptr);
    EXPECT_NE(bob_private_key, nullptr);

    EVP_PKEY_free_ptr alice_public_key =
        ExtractPublicKey(alice_private_key.get());
    EVP_PKEY_free_ptr bob_public_key = ExtractPublicKey(bob_private_key.get());

    EXPECT_NE(alice_public_key, nullptr);
    EXPECT_NE(bob_public_key, nullptr);

    std::string alice_key = SerializePublicKey(alice_public_key.get());
    std::cout << "alice: " << alice_key << std::endl;

    std::string bob_key = SerializePublicKey(bob_public_key.get());
    std::cout << "bob: " << bob_key << std::endl;

    EXPECT_NE(bob_key, alice_key);

    EVP_PKEY_free_ptr alice_peer_key = DeserializePublicKey(bob_key.c_str());
    EVP_PKEY_free_ptr bob_peer_key = DeserializePublicKey(alice_key.c_str());

    DerivedData* secret_alice =
        DeriveSharedSecret(alice_peer_key.get(), alice_private_key.get());
    DerivedData* secret_bob =
        DeriveSharedSecret(bob_peer_key.get(), bob_private_key.get());

    std::cout << "alice secret: " << *(secret_alice->secret) << std::endl;
    std::cout << "bob secret: " << *(secret_bob->secret) << std::endl;
    std::cout << "alice secret length: " << secret_alice->length << std::endl;
    std::cout << "bob secret length: " << secret_bob->length << std::endl;

    EXPECT_EQ(*(secret_alice->secret), *(secret_bob->secret));
    EXPECT_EQ(secret_alice->length, secret_bob->length);

    free(secret_alice->secret);
    free(secret_bob->secret);
    free(secret_alice);
    free(secret_bob);
  }
}