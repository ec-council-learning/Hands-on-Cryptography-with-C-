// src/aes.cpp
#include <cryptopp/cryptlib.h> // SecByteBlock
#include <cryptopp/osrng.h> // AutoSeededRandomPool
#include <cryptopp/modes.h> // CBC_Mode
#include <cryptopp/rijndael.h> // AES
#include "aes.h"

// for convenience
using namespace CryptoPP;

std::string Randomizer::aes_encrypt(
  std::string plain
) {
  // pre-allocate key for 32 bytes and IV for 16 bytes
  SecByteBlock key(32);
  SecByteBlock iv(16);
  AutoSeededRandomPool rng;
  std::string cipher;

  // generates the 32-bytes key and 16-bytes IV
  rng.GenerateBlock(key, key.size());
  rng.GenerateBlock(iv, iv.size());

  // prepares the AES algorithm
  CBC_Mode<AES>::Encryption aes_algo;
  aes_algo.SetKeyWithIV(key, key.size(), iv);

  // performs the AES encryption
  StringSource source(plain, true, new StreamTransformationFilter(
    aes_algo,
    new StringSink(cipher)
  ));

  return cipher;
}