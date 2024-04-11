// src/signer.h
#ifndef __CURVYPP_SIGNER_H__
#define __CURVYPP_SIGNER_H__

#include <string>
#include <cryptopp/filters.h> // StringSource, StringSink, SignerFilter
#include <cryptopp/osrng.h> // AutoSeededRandomPool
#include <cryptopp/hex.h> // HexEncoder

namespace CurvyPP {

  /// \brief Wrapper class to manage digital signatures
  template <typename SignerImpl>
  class Signer
  {
  public:
    SignerImpl m_signer;

    /// \brief Creates a new keypair instance
    Signer(SignerImpl signer)
      : m_signer(signer)
    {}

    /// \brief Signs a message and returns the signature payload (base64-encoded)
    std::string Sign(std::string message)
    {
      std::string signature, sig_payload;
      CryptoPP::AutoSeededRandomPool prng;

      // true = "pump-all"
      CryptoPP::StringSource sig_source(message, true, new CryptoPP::SignerFilter(prng,
        m_signer,
        new CryptoPP::StringSink(signature)
      ));

      CryptoPP::StringSource hex_source(signature, true,  new CryptoPP::HexEncoder(
        new CryptoPP::StringSink(sig_payload)
      ));

      return sig_payload;
    }
  };

}

#endif