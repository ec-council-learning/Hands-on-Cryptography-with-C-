// src/botan.h
#ifndef __ZTHANKS_BOTAN_H__
#define __ZTHANKS_BOTAN_H__

namespace ztx {
namespace botan {

  /// \brief Encrypts a message using Camellia-256 (Botan).
  std::string Encrypt(const std::string&);

  /// \brief Hashes a message using Whirlpool (Botan).
  std::string Hash_Function(const std::string&);

  /// \brief Generates a random private key and signs the message (Botan).
  std::string Sign_ECDSA(const std::string&);

  /// \brief Generates a random shared secret for ECDH (Botan).
  std::string GetSecret_ECDH();

}
}
#endif