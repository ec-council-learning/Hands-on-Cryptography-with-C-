// src/functions.cpp
#include "functions.h"
#include <vector>
#include <botan/auto_rng.h>
#include <botan/block_cipher.h>
#include <botan/hex.h>
#include <botan/ecdsa.h>
#include <botan/ec_group.h>
#include <botan/pkcs8.h>
#include <botan/hash.h>

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