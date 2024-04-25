// src/functions.cpp
#include "functions.h"
#include <vector> // std::vector
#include <botan/auto_rng.h> // AutoSeeded_RNG
#include <botan/block_cipher.h> // BlockCipher
#include <botan/hex.h> // hex_encode
#include <botan/ecdsa.h> // ECDSA_PrivateKey
#include <botan/ec_group.h> // EC_Group
#include <botan/pkcs8.h> // PKCS8::PEM_encode
#include <botan/hash.h> // HashFunction

Botan::AutoSeeded_RNG g_rng;

std::string encrypt(std::string input) {
  std::vector<uint8_t> cipher(input.begin(), input.end());
  const auto enc = Botan::BlockCipher::create_or_throw("Serpent");
  const auto key = g_rng.random_vec(32);
  enc->set_key(key);
  enc->encrypt(cipher); // cipher passed by reference
  return Botan::hex_encode(cipher);
}

std::string pem_encoded_key() {
  Botan::ECDSA_PrivateKey ecdsa_key(g_rng, Botan::EC_Group("secp256r1"));
  return Botan::PKCS8::PEM_encode(ecdsa_key, g_rng, "");
}

std::string whirlpool_hash(std::string input) {
  std::vector<uint8_t> bytes(input.begin(), input.end());
  const auto hash = Botan::HashFunction::create_or_throw("Whirlpool");
  hash->update(bytes);
  return Botan::hex_encode(hash->final());
}