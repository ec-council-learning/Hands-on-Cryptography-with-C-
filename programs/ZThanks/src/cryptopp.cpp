// src/cryptopp.cpp
#include <cryptopp/default.h> // DefaultEncryptor, DefaultDecryptor
#include <cryptopp/filters.h> // StringSink, StringSource
#include <cryptopp/base64.h> // Base64Encoder, Base64Decoder
#include <cryptopp/hex.h> // HexEncoder
#include <cryptopp/sha.h> // SHA256
#include <cryptopp/xed25519.h> // ed25519..
#include <cryptopp/osrng.h> // AutoSeededRandomPool
#include <cryptopp/eccrypto.h> // ECDH, ECP, SHA256
#include <cryptopp/oids.h> // ASN1::secp256r1
#include "cryptopp.h"

using CryptoPP::ECP, CryptoPP::OID;
using CryptoPP::SecByteBlock;

std::string ztx::cryptopp::Encrypt(const std::string& message) {
  std::string cipher, output;

  // Encrypt using AES-256 and password
  CryptoPP::StringSource enc_source(message, true, new CryptoPP::DefaultEncryptor(
    "Hands-On Cryptography with C++",
    new CryptoPP::StringSink(cipher)
  ));

  // Format the ciphertext with base64
  CryptoPP::StringSource b64_source(cipher, true,  new CryptoPP::Base64Encoder(
    new CryptoPP::StringSink(output),
    false // no line breaks
  ));

  return output.c_str();
}

std::string ztx::cryptopp::Hash_Function(const std::string& message) {
  std::string output;
  CryptoPP::SHA256 hash;

  // Hash the message using SHA-256
  CryptoPP::StringSource source(message, true, new CryptoPP::HashFilter(
    hash,
    new CryptoPP::HexEncoder(new CryptoPP::StringSink(output))
  ));

  return output;
}

std::string ztx::cryptopp::Sign_ECDSA(const std::string& message) {
  CryptoPP::AutoSeededRandomPool prng;

  // Generates a random private key
  auto signer = CryptoPP::ed25519Signer();
  signer.AccessPrivateKey().GenerateRandom(prng);

  std::string signature, sig_payload;

  // Signs the message using the private key
  // true = "pump-all"
  CryptoPP::StringSource sig_source(message, true, new CryptoPP::SignerFilter(prng,
    signer,
    new CryptoPP::StringSink(signature)
  ));

  // Formats the signature in hexadecimal format
  CryptoPP::StringSource hex_source(signature, true,  new CryptoPP::HexEncoder(
    new CryptoPP::StringSink(sig_payload)
  ));

  return sig_payload;
}

std::string ztx::cryptopp::GetSecret_ECDH() {
  // NIST's 256 bit curve over f(p)
  OID CURVE = CryptoPP::ASN1::secp256r1();
  CryptoPP::AutoSeededRandomPool prng;
  std::string shared_secret;

  // prepares 2 keypairs ("Alice" and "Bob")
  // usually Alice and Bob would be on different devices
  CryptoPP::ECDH<ECP>::Domain alice(CURVE),
                              bob(CURVE);
  SecByteBlock alice_privateKey(alice.PrivateKeyLength()),
               alice_publicKey(alice.PublicKeyLength());
  SecByteBlock bob_privateKey(bob.PrivateKeyLength()),
               bob_publicKey(bob.PublicKeyLength());

  // generates the random keypairs
  alice.GenerateKeyPair(prng, alice_privateKey, alice_publicKey);
  bob.GenerateKeyPair(prng, bob_privateKey, bob_publicKey);

  // Alice and Bob shall agree on a shared secret
  SecByteBlock alice_shared(alice.AgreedValueLength()),
               bob_shared(bob.AgreedValueLength());

  // creates the secret from Alice's perspective
  alice.Agree(alice_shared, alice_privateKey, bob_publicKey); // A -> B

  // creates the secret from Bob's perspective
  bob.Agree(bob_shared, bob_privateKey, alice_publicKey); // B -> A

  // Formats the shared secret in hexadecimal format
  CryptoPP::HexEncoder key_encoder(new CryptoPP::StringSink(shared_secret));
  key_encoder.Put((const CryptoPP::byte*) alice_shared.data(), alice_shared.size());
  key_encoder.MessageEnd();

  return shared_secret;
}
