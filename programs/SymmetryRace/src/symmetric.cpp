// src/symmetric.cpp
#include "symmetric.h"
#include <botan/auto_rng.h> // AutoSeeded_RNG
#include <botan/base64.h> // base64_encode
#include <botan/block_cipher.h> // SymmetricKey
#include <botan/pipe.h> // Pipe
#include <botan/filters.h> // get_cipher

std::string SymmetryRace::SymmetricCipher::generate_key() {
  Botan::AutoSeeded_RNG rng;
  return m_key = Botan::base64_encode(rng.random_vec(m_key_size));
}

std::string SymmetryRace::SymmetricCipher::encrypt(std::string input) const {
  if (m_key.empty()) {
    throw std::runtime_error("Missing call to generate_key()");
  }

  Botan::SymmetricKey key(Botan::base64_decode(m_key));
  Botan::Pipe pipe(
    Botan::get_cipher(get_algorithm(), key, Botan::Cipher_Dir::Encryption),
    new Botan::Base64_Encoder
  );

  pipe.process_msg(input);
  return pipe.read_all_as_string();
}

std::string SymmetryRace::SymmetricCipher::decrypt(std::string input) const {
  if (m_key.empty()) {
    throw std::runtime_error("Missing call to generate_key()");
  }

  Botan::SymmetricKey key(Botan::base64_decode(m_key));
  Botan::Pipe pipe(
    new Botan::Base64_Decoder,
    Botan::get_cipher(get_algorithm(), key, Botan::Cipher_Dir::Decryption)
  );

  pipe.process_msg(input);
  return pipe.read_all_as_string();
}