// src/camellia.cpp
#include "camellia.h" // CamelliaBreed
#include <botan/block_cipher.h> // SymmetricKey
#include <botan/base64.h> // Base64Encoder, Base64Decoder
#include <botan/pipe.h> // Pipe
#include <botan/filters.h> // get_cipher

std::string BeeTransport::CamelliaBreed::name() const {
  return get_algorithm();
}

std::string BeeTransport::CamelliaBreed::encrypt(std::string input) const {
  Botan::SymmetricKey key(Botan::base64_decode(m_key));
  Botan::Pipe pipe(
    Botan::get_cipher(get_algorithm(), key, Botan::Cipher_Dir::Encryption),
    new Botan::Base64_Encoder
  );

  pipe.process_msg(input);
  return pipe.read_all_as_string();
}

std::string BeeTransport::CamelliaBreed::decrypt(std::string input) const {
  Botan::SymmetricKey key(Botan::base64_decode(m_key));
  Botan::Pipe pipe(
    new Botan::Base64_Decoder,
    Botan::get_cipher(get_algorithm(), key, Botan::Cipher_Dir::Decryption)
  );

  pipe.process_msg(input);
  return pipe.read_all_as_string();
}