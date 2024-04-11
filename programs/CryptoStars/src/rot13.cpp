// src/rot13.cpp
#include "rot13.h"

int CryptoStars::ROT13::Compute()
{
  // Computation cannot happen without a message
  if (m_vargs.end() == m_vargs.find("message")) {
    return 1;
  }

  // platform specific offset for alphabet
  unsigned int offset = 'a' - 1;
  std::string input = m_vargs["message"], output;

  for (const auto& character : input) {
    if (0 == isalpha(character)) {
      output.append(1, character);
      continue;
    }

    // ROT13 shifts characters right-or-left depending
    // on their position in the alphabet, encryption and
    // decryption do not differ using this algorithm (self-inverting).
    char shifted;
    shifted = (tolower(character) - offset) < 14
      ? character + 13
      : character - 13;

    output.append(1, shifted);
  }

  m_results["ciphertext"] = output;
  return 0;
}