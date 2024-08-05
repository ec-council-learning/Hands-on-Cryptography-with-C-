// src/asymmetric.cpp
#include "asymmetric.h"
#include <botan/auto_rng.h> // AutoSeeded_RNG
#include <botan/hex.h> // base64_encode
#include <botan/rsa.h> // RSA_PrivateKey
#include <botan/pkcs8.h> // PEM_encode
#include <botan/pk_keys.h> // PrivateKey, PublicKey
#include <botan/pubkey.h> // PK_Encryptor_X

std::string SymmetryRace::AsymmetricCipher::encrypt(std::string input) const {
  if (m_key.empty()) {
    throw std::runtime_error("Missing call to generate_key()");
  }

  Botan::AutoSeeded_RNG rng;
  std::vector<uint8_t> key_bytes(m_key.begin(), m_key.end());
  Botan::DataSource_Memory in(key_bytes);
  auto key = Botan::PKCS8::load_key(in, "");
  Botan::PK_Encryptor_EME enc(*key, rng, get_padding_scheme());

  std::vector<uint8_t> bytes(input.data(), input.data() + input.length());
  std::vector<uint8_t> cipher = enc.encrypt(bytes, rng);
  return Botan::hex_encode(cipher);
}

std::string SymmetryRace::AsymmetricCipher::decrypt(std::string input) const {
  if (m_key.empty()) {
    throw std::runtime_error("Missing call to generate_key()");
  }

  Botan::AutoSeeded_RNG rng;
  std::vector<uint8_t> key_bytes(m_key.begin(), m_key.end());
  Botan::DataSource_Memory in(key_bytes);
  auto key = Botan::PKCS8::load_key(in, "");
  Botan::PK_Decryptor_EME dec(*key, rng, get_padding_scheme());

  std::vector<uint8_t> bytes = Botan::hex_decode(input);
  Botan::secure_vector<uint8_t> plain = dec.decrypt(bytes);
  return std::string(plain.begin(), plain.end());
}

std::string SymmetryRace::RSA::generate_key() {
  Botan::AutoSeeded_RNG rng;
  Botan::RSA_PrivateKey key(rng, m_key_size);
  return m_key = Botan::PKCS8::PEM_encode(key, rng, ""); // empty password!
}
