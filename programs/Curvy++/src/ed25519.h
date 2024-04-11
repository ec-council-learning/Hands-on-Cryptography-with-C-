// src/ed25519.h
#ifndef __CURVYPP_ED25519_H__
#define __CURVYPP_ED25519_H__

#include <cryptopp/xed25519.h> // ed25519..
#include <cryptopp/osrng.h> // AutoSeededRandomPool
#include "keypair.h"

namespace CurvyPP::Ed25519 {

  using SignerImpl = CryptoPP::ed25519Signer;
  using PrivateKeyImpl = CryptoPP::ed25519PrivateKey;
  using PublicKeyImpl = CryptoPP::ed25519PublicKey;

  /// \brief An ed25519 specialization of the KeyPair class for Curve25519
  class KeyPair
    : public CurvyPP::KeyPair<SignerImpl, PrivateKeyImpl, PublicKeyImpl>
  {
  public:
    /// \brief Generates a random pair of private- and public-key.
    void GenerateRandom()
    {
      CryptoPP::AutoSeededRandomPool prng;

      // creates a random private exponent
      m_signer = SignerImpl();
      m_signer.AccessPrivateKey().GenerateRandom(prng);

      // store the private key
      m_privateKey = dynamic_cast<const PrivateKeyImpl&>(m_signer.GetPrivateKey());

      // creates the public element
      m_privateKey.MakePublicKey(m_publicKey);
    }

    /// \brief Retrieves a string-typed hexadecimal format of the public key.
    std::string GetPublicKey() {
      return CurvyPP::Format::key_to_hex(m_publicKey.GetPublicElement());
    }
  };

}

#endif