// src/random.h
#include <cryptopp/osrng.h>

namespace Randomizer {

  /// \brief Generates a block of random bytes using AutoSeededRandomPool
  CryptoPP::SecByteBlock generate_random(
    size_t size
  );

  /// \brief Generates a block of random bytes using LC_RNG
  CryptoPP::SecByteBlock generate_random_lc(
    size_t size
  );

}