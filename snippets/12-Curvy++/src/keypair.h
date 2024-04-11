// src/keypair.h
#ifndef __CURVYPP_KEYPAIR_H__
#define __CURVYPP_KEYPAIR_H__
#include <string> // std::string
#include "format.h" // key_to_hex
#include "signer.h"

namespace CurvyPP {

  /// \brief Wrapper class to manage key-pair objects for multiple curves
  template <class SignerImpl, class PrivateKeyImpl, class PublicKeyImpl>
  class KeyPair
  {
  protected:
    PrivateKeyImpl m_privateKey;
    SignerImpl m_signer;

  public:
    PublicKeyImpl m_publicKey;

    KeyPair() {}

    virtual void GenerateRandom() = 0;
    virtual std::string GetPublicKey() = 0;

    std::string GetPrivateKey() {
      return CurvyPP::Format::key_to_hex(m_privateKey.GetPrivateExponent());
    }

    /// \brief Signs a message and returns the signature payload (base64-encoded)
    std::string Sign(std::string message) {
      auto signer = new CurvyPP::Signer<SignerImpl>(m_signer);
      return signer->Sign(message);
    }
  };

}
#endif