// src/main.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <cryptopp/osrng.h>
#include "random.h"
#include "aes.h"
#include "utils.h"

using Randomizer::Utils::print_buffer;
using Randomizer::Utils::print_cipher;

int main()
{
  // generates a random 32 bytes block
  CryptoPP::SecByteBlock key = Randomizer::generate_random(32);
  CryptoPP::SecByteBlock key_lc = Randomizer::generate_random_lc(32);

  // display generated random bytes (auto-seeded)
  std::cout << "The auto-seeded random 32 bytes are:    ";
  print_buffer(key);

  // display generated random bytes (linear congruential)
  std::cout << "The LC_RNG random 32 bytes are:         ";
  print_buffer(key_lc);

  // performs AES encryption
  std::string cipher = Randomizer::aes_encrypt("Hello, world!");
  std::cout << "The AES ciphertext (base64-encoded) is: ";
  print_cipher(cipher);

  return 0;
}