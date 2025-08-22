// src/botan.cpp
#include <botan/block_cipher.h> // SymmetricKey
#include <botan/base64.h> // Base64Encoder, Base64Decoder
#include <botan/pipe.h> // Pipe
#include <botan/filters.h> // get_cipher
#include <botan/hash.h> // HashFunction
#include <botan/hex.h> // hex_encode
#include <botan/auto_rng.h> // AutoSeeded_RNG
#include <botan/ec_group.h> // EC_Group
#include <botan/pubkey.h> // PK_Signer
#include <botan/ecdsa.h> // ECDSA_PrivateKey, ECDSA_PublicKey
#include <botan/ecdh.h> // ECDH_PrivateKey
#include "botan.h"

std::string ztx::botan::Encrypt(const std::string& message) {
  // Compute sha-256 of password to use as key
  auto hash = Botan::HashFunction::create_or_throw("SHA-256");
  hash->update("Hands-On Cryptography with C++");
  auto key = hash->final();

  // Uses a sha-256 hash of the password as the key
  Botan::SymmetricKey k(key);

  // Encrypts using Camellia-256 and hash of password
  Botan::Pipe pipe(
    Botan::get_cipher("Camellia-256/CBC", k, Botan::Cipher_Dir::Encryption),
    new Botan::Base64_Encoder
  );

  pipe.process_msg(message);
  return pipe.read_all_as_string();
}

std::string ztx::botan::Hash_Function(const std::string& message) {
  std::vector<uint8_t> bytes(message.begin(), message.end());

  // Hash the message using Whirlpool
  const auto hash = Botan::HashFunction::create_or_throw("Whirlpool");
  hash->update(bytes);

  return Botan::hex_encode(hash->final());
}

std::string ztx::botan::Sign_ECDSA(const std::string& message) {
  Botan::AutoSeeded_RNG rng;

  // Generates a random private key
  auto priv = std::make_unique<Botan::ECDSA_PrivateKey>(
    rng, Botan::EC_Group("secp256r1")
  );

  // Signs the message using the private key
  Botan::PK_Signer signer(*priv, rng, "SHA-256");
  signer.update(message);
  std::vector<uint8_t> sig = signer.signature(rng);

  return Botan::hex_encode(sig);
}

std::string ztx::botan::GetSecret_ECDH() {
  Botan::AutoSeeded_RNG rng;

  // ec domain and KDF
  const auto CURVE = Botan::EC_Group("secp256r1");
  const std::string kdf = "KDF2(SHA-256)";

  // the two parties generate ECDH keys
  Botan::ECDH_PrivateKey alice_privateKey(rng, CURVE);
  Botan::ECDH_PrivateKey bob_privateKey(rng, CURVE);

  // now they exchange their public values
  const auto alice_publicKey = alice_privateKey.public_value();
  const auto bob_publicKey   = bob_privateKey.public_value();

  // Construct key agreements and agree on a shared secret
  Botan::PK_Key_Agreement ka_a(alice_privateKey, rng, kdf);
  const auto sA = ka_a.derive_key(32, bob_publicKey).bits_of();

  Botan::PK_Key_Agreement ka_b(bob_privateKey, rng, kdf);
  const auto sB = ka_b.derive_key(32, alice_publicKey).bits_of();

  return Botan::hex_encode(sA);
}