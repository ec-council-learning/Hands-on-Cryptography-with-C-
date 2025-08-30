// src/cipher.cpp
#include "cipher.h"
#include <botan/block_cipher.h> // SymmetricKey
#include <botan/base64.h> // Base64Encoder, Base64Decoder
#include <botan/pipe.h> // Pipe
#include <botan/filters.h> // get_cipher
#include <botan/hex.h> // hex_encode

std::string WhatBlock::Cipher::decrypt(std::string input) const {
  Botan::SymmetricKey key(Botan::base64_decode(m_key));
  Botan::Pipe pipe(
    new Botan::Base64_Decoder,
    Botan::get_cipher(get_algorithm(), key, Botan::Cipher_Dir::Decryption)
  );

  pipe.process_msg(input);
  return pipe.read_all_as_string();
}

/// \todo Add debug information for block-by-block encryption
std::string WhatBlock::Cipher::encrypt(std::string input) const {
  // Quick string-to-byte-vector
  std::vector<uint8_t> bytes(input.begin(), input.end()),
                       cipher;

  // As usual, we initialize the block cipher with our key
  Botan::SymmetricKey key(Botan::base64_decode(m_key));
  Botan::Pipe pipe(
    Botan::get_cipher(get_algorithm(), key, Botan::Cipher_Dir::Encryption),
    new Botan::Base64_Encoder
  );

  // PKCS5 Padding: Makes sure that data is padded
  // to a size that is a multiple of the BLOCKSIZE
  size_t old_size = bytes.size();
  if (0 != bytes.size() % m_block_size) {
    // padding m bytes with m value
    size_t bs = m_block_size,
           m = (bs - old_size % bs) % bs;
    bytes.resize(old_size + m, m);
  }
  else {
    // adding one block filled with block_size bytes
    bytes.resize(old_size + m_block_size, m_block_size);
  }

  // Starts a message route in our pipeline
  pipe.start_msg();

  // We encrypt block-by-block
  unsigned int num_blocks = bytes.size() / m_block_size;
  for (unsigned int i = 0; i < num_blocks; i++) {
    // Creates a byte-vector the size of a block
    std::vector<uint8_t> block(m_block_size);
    std::copy(
      bytes.begin() + (i * m_block_size),
      bytes.begin() + (i * m_block_size) + m_block_size,
      block.begin()
    );

    // Adds the block data to our pipeline
    pipe.write(block);
  }

  // Ends a message route in our pipeline
  pipe.end_msg();
  return pipe.read_all_as_string();
}