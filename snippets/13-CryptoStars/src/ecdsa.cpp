// src/ecdsa.cpp
#include <cryptopp/filters.h> // StringSink
#include <cryptopp/hex.h> // HexEncoder, HexDecoder
#include <cryptopp/base64.h> // Base64Encoder, Base64Decoder
#include <cryptopp/osrng.h> // AutoSeededRandomPool
#include <cryptopp/eccrypto.h> // ECDSA, ECP, SHA256
#include <cryptopp/oids.h> // ASN1::secp256k1
#include "format.h" // key_to_hex, bytes_to_hex
#include "ecdsa.h"

using CryptoPP::ECDSA, CryptoPP::ECP, CryptoPP::SHA256, CryptoPP::byte;
using SignerImpl = ECDSA<ECP, SHA256>::Signer;
using VerifierImpl = ECDSA<ECP, SHA256>::Verifier;
using PrivateKeyImpl = ECDSA<ECP, SHA256>::PrivateKey;
using PublicKeyImpl = ECDSA<ECP, SHA256>::PublicKey;
using CryptoStars::Format::key_to_hex;
using CryptoStars::Format::bytes_to_hex;

int CryptoStars::ECDSA::Compute() {
  // Computation cannot happen without a message
  if (m_vargs.end() == m_vargs.find("message")) {
    return 1;
  }

  // reads parameters
  std::string input = m_vargs["message"];

  /* Operation::Sign */
  if (m_op == Operation::Sign) {
    return DoSign(input);
  }

  /* Operation::Verify */
  std::string publicKey = m_vargs["publicKey"],
              signature = m_vargs["signature"];
  return DoVerify(publicKey, input, signature);
}

int CryptoStars::ECDSA::DoSign(const std::string& input) {
  std::string signature, pub_payload;
  CryptoPP::AutoSeededRandomPool prng;

  // generates a random keypair
  PrivateKeyImpl private_key;
  PublicKeyImpl  public_key;
  private_key.Initialize(prng, CryptoPP::ASN1::secp256k1());
  private_key.MakePublicKey(public_key);

  // stores the public key in a DER-encoded base64 envelope (PEM)
  CryptoPP::Base64Encoder pubkey_sink(new CryptoPP::StringSink(pub_payload), false);
  public_key.DEREncode(pubkey_sink);
  pubkey_sink.MessageEnd();

  // creates the signer interface
  SignerImpl signer(private_key);
  size_t length = signer.MaxSignatureLength();
  CryptoPP::SecByteBlock signatureRaw(length);

  // signs the message
  signer.SignMessage(prng, (const byte*) input.data(), input.size(), signatureRaw);

  m_results["privateKey"] = key_to_hex(private_key.GetPrivateExponent());
  m_results["publicKey"] = pub_payload; // PEM format (base64 of DER-encoded key)
  m_results["signature"] = bytes_to_hex(signatureRaw);
  return 0;
}

int CryptoStars::ECDSA::DoVerify(
  const std::string& publicKeyEncoded,
  const std::string& input,
  const std::string& signatureHex
) {
  std::string sig_bytes;

  // decodes the public key PEM and signature hex
  CryptoPP::StringSource b64_public(publicKeyEncoded, true, new CryptoPP::Base64Decoder);
  CryptoPP::StringSource hex_signature(signatureHex, true, new CryptoPP::HexDecoder(
    new CryptoPP::StringSink(sig_bytes))
  );

  // loads the public key using decoded PEM
  PublicKeyImpl publicKey;
  publicKey.BERDecode(b64_public);
  VerifierImpl verifier(publicKey);

  // verifiable message is: signature || message
  bool result = false;
  std::string ciphertext = sig_bytes + input;
  CryptoPP::StringSource sig_source(ciphertext, true /* pump-all */,
    new CryptoPP::SignatureVerificationFilter(
      verifier,
      new CryptoPP::ArraySink((byte*)&result, sizeof(result))
    ));

  m_results["verified"] = result ? "VALID (OK)" : "NOT VALID (NOT OK)";
  return 0;
}