// src/secp256k1.h
#ifndef __CURVYPP_SECP256K1_H_
#define __CURVYPP_SECP256K1_H_

#include <iomanip>
#include <sstream>
#include <cryptopp/eccrypto.h> // ECDSA, ECP, SHA256
#include <cryptopp/osrng.h> // AutoSeededRandomPool
#include <cryptopp/oids.h> // ASN1::secp256k1
#include "keypair.h"

namespace CurvyPP::Secp256 {

  using CryptoPP::ECDSA, CryptoPP::ECP, CryptoPP::SHA256;
  using SignerImpl = ECDSA<ECP, SHA256>::Signer;
  using PrivateKeyImpl = ECDSA<ECP, SHA256>::PrivateKey;
  using PublicKeyImpl = ECDSA<ECP, SHA256>::PublicKey;
  using CurvyPP::Format::key_to_hex;

  /// \brief A secp256 specialization of the KeyPair class for curve SEC prime 256
  class KeyPair
    : public CurvyPP::KeyPair<SignerImpl, PrivateKeyImpl, PublicKeyImpl>
  {
  public:
    /// \brief Generates a random pair of private- and public-key.
    void GenerateRandom()
    {
      // creates the private exponent
      CryptoPP::AutoSeededRandomPool prng;
      m_privateKey.Initialize(prng, CryptoPP::ASN1::secp256k1());

      // creates the public element
      m_privateKey.MakePublicKey(m_publicKey);

      // creates the signer interface
      m_signer = SignerImpl(m_privateKey);
    }

    /// \brief Retrieves a string-typed hexadecimal format of the public key.
    std::string GetPublicKey() {
      // reads the public key (64 bytes)
      ECP::Point q = m_publicKey.GetPublicElement();

      // streams to a hex-encoder
      return key_to_hex(q.x) + key_to_hex(q.y);
    }
  };

}

#endif