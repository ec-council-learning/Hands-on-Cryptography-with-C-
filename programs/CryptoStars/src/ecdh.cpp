// src/ecdh.cpp
#include <cryptopp/osrng.h> // AutoSeededRandomPool
#include <cryptopp/eccrypto.h> // ECDH, ECP, SHA256
#include <cryptopp/oids.h> // ASN1::secp256r1
#include "format.h" // key_to_hex
#include "ecdh.h"

using CryptoPP::ECP, CryptoPP::OID;
using CryptoPP::SecByteBlock;
using CryptoStars::Format::key_to_hex;
using CryptoStars::Format::bytes_to_hex;

int CryptoStars::ECDH::Compute()
{
  // NIST's 256 bit curve over f(p)
  OID CURVE = CryptoPP::ASN1::secp256r1();
  CryptoPP::AutoSeededRandomPool prng;

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

  // ECDH works with 2 users so the results are many..
  m_results["Alice.privateKey"] = bytes_to_hex(alice_privateKey);
  m_results["Alice.publicKey"] = bytes_to_hex(alice_publicKey);
  m_results["Alice.sharedSecret"] = bytes_to_hex(alice_shared);
  m_results["Bob.privateKey"] = bytes_to_hex(bob_privateKey);
  m_results["Bob.publicKey"] = bytes_to_hex(bob_publicKey);
  m_results["Bob.sharedSecret"] = bytes_to_hex(bob_shared);
  return 0;
}