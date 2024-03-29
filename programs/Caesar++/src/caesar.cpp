// src/caesar.cpp
#include "caesar.h"
#include <cctype>

// platform specific offset for alphabets
// on UNIX upper=64, lower=96
const unsigned int offset_lower = 'a' - 1,
                   offset_upper = 'A' - 1;

void CaesarPP::CaesarStreamTransformation::ProcessData(
  CryptoPP::byte *outString,
  const CryptoPP::byte *inString,
  size_t length
) {
  for (int i = 0; i < length; i++, inString++, outString++) {
    // character is expressed as a byte
    const auto character = *inString;

    // non-alphabet characters gets ignored
    if (0 == std::isalpha(character)) {
      *outString = character;
      continue;
    }

    // right-shift of 3 ("Caesar" shift cipher)
    *outString = character + 3;

    // loop in alphabets (lower to lower, upper to upper)
    // this implements the "wrapping" in Caesar Cipher
    if (
        (character < offset_lower && *outString > offset_lower) ||
        (character >= offset_lower && *outString > offset_lower + 26)
    ) {
        *outString = *outString - 26;
    }

  }
}