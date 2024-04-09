// src/random.cpp
#include "random.h"

CryptoPP::SecByteBlock Randomizer::generate_random(
  size_t size
) {
  // pre-allocate for x bytes
  CryptoPP::SecByteBlock key(size);
  CryptoPP::AutoSeededRandomPool rng;

  // generates a 32 bytes block
  rng.GenerateBlock(key, key.size());

  // and returns the result
  return key;
}

CryptoPP::SecByteBlock Randomizer::generate_random_lc(
  size_t size
) {
  // pre-allocate for x bytes
  CryptoPP::SecByteBlock key(size);
  CryptoPP::LC_RNG rng(2249167231); // <- seeded randomness

  // generates a 32 bytes block
  rng.GenerateBlock(key, key.size());

  // and returns the result
  return key;
}