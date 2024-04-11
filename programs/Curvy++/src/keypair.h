// src/keypair.h
#ifndef __CURVYPP_KEYPAIR_H__
#define __CURVYPP_KEYPAIR_H__

#include <string>
#include "format.h"
#include "signer.h"

namespace CurvyPP {

  /// \brief Wrapper class to manage key-pair objects for multiple curves
  template <class SignerImpl, class PrivateKeyImpl, class PublicKeyImpl>
  class KeyPair
  {
  public:
    PrivateKeyImpl m_privateKey; // <-- public for convenience (caution!)
    PublicKeyImpl m_publicKey;
    SignerImpl m_signer;

    /// \brief Creates a new keypair instance
    KeyPair() {}

    /// \brief Generates a random pair of private- and public-key.
    virtual void GenerateRandom() = 0;

    /// \brief Retrieves a string-typed hexadecimal format of the public key.
    virtual std::string GetPublicKey() = 0;

    /// \brief Retrieves a string-typed hexadecimal format of the private key.
    std::string GetPrivateKey() {
      return CurvyPP::Format::key_to_hex(m_privateKey.GetPrivateExponent());
    }

    /// \brief Signs a message and returns the signature payload (base64-encoded)
    std::string Sign(std::string message)
    {
      auto signer = new CurvyPP::Signer<SignerImpl>(m_signer);
      return signer->Sign(message);
    }
  };

}

#endif