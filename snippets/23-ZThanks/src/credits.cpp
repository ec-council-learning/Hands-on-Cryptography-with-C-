// src/credits.cpp
#include <vector> // std::vector
#include <sstream> // std::stringstream
#include "botan.h" // ztx::botan
#include "cryptopp.h" // ztx::cryptopp
#include "credits.h" // ZCredits

ztx::ZCredits::ZCredits(
  const std::string& msg
) : m_message(msg)
{
  // Encryption algorithms
  m_ciphers["a. AES-256"] = ztx::cryptopp::Encrypt(m_message);
  m_ciphers["b. Camellia"]   = ztx::botan::Encrypt(m_message);

  // Hash functions
  m_ciphers["c. SHA-256"] = ztx::cryptopp::Hash_Function(m_message);
  m_ciphers["d. Whirlpool"]  = ztx::botan::Hash_Function(m_message);

  // Digital signature algorithms
  m_ciphers["e. ECDSA_A"] = ztx::cryptopp::Sign_ECDSA(m_message);
  m_ciphers["f. ECDSA_B"]    = ztx::botan::Sign_ECDSA(m_message);

  // Key Agreement schemes
  m_ciphers["g. ECDH_A"] = ztx::cryptopp::GetSecret_ECDH();
  m_ciphers["h. ECDH_B"]    = ztx::botan::GetSecret_ECDH();
}

ztx::ZCredits::operator std::string() const {
  std::stringstream stream;

  // first print the plaintext credits message
  stream << "Message: " << m_message << std::endl << std::endl;

  // then print individual ciphertexts and hashes
  // as produced with Crypto++ and Botan frameworks.
  stream <<   "------------";
  for (auto it = m_ciphers.begin(); it != m_ciphers.end(); it++) {
    stream << std::endl
           << it->first << ": \t";

    stream << Stream_Value(it->second);
  }
  stream << std::endl << "------------" << std::endl;

  stream << std::endl
         << "This course was written and produced by Grégory Saive <greg@evi.as>," << std::endl 
         << "in collaboration with ECCouncil.org. Find me here: https://evi.as";

  stream << std::flush;
  return stream.str();
}

std::string ztx::ZCredits::Stream_Value(
  const std::string& val
) const {
  std::stringstream s;
  auto val_size = val.size();
  if (val_size <= 64) {
    s << val;
  }
  else {
    int lines = (int) val_size / 64;
    for (int i = 0; i < lines; i++) {
      auto tab = i > 0 ? "\t\t" : "";
      auto eol = i < lines-1 ? "\n" : "";
      s << tab << val.substr(i*64, 64) << eol;
    }
  }

  return s.str();
}
