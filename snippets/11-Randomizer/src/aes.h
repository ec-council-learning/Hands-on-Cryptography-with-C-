// src/aes.h
#include <string> // std::string

namespace Randomizer {

  /// \brief Performs AES encryption using a random 32-bytes key
  std::string aes_encrypt(
    std::string plain
  );

}