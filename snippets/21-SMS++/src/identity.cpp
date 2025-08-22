// src/identity.cpp
#include "identity.h"
#include <botan/auto_rng.h> // Botan::AutoSeeded_RNG
#include <botan/ec_group.h> // Botan::EC_Group
#include <botan/pkcs8.h> // Botan::PKCS8::load_key
#include <botan/x509_key.h> // Botan::X509::PEM_encode
#include <botan/pk_keys.h> // Botan::Public_Key
#include <botan/hash.h> // Botan::HashFunction
#include <botan/hex.h> // Botan::hex_encode
#include <filesystem> // std::filesystem
#include <fstream> // std::ofstream

/// \brief Default constructor. Creates and initializes an ECDH identity
///        using the \a id_file identity file if it exists, or creates a
///        random ECDH private key if the file doesn't exist.
SMSpp::Identity::Identity(const std::string& id_file)
  : m_params(std::make_unique<Botan::ECIES_System_Params>(
    Botan::EC_Group("secp256r1"),
    "KDF2(SHA-256)",
    "AES-256/CBC", 32,
    "HMAC(SHA-256)", 32
  ))
{
  std::filesystem::directory_entry entry{id_file};

  // loads an identity from file using (PEM-encoded or DER-encoded)
  if (entry.exists()) {
    Import(id_file);
  }
  // or creates a new identity and exports to file data/id_ecdh.smsid
  else {
    GenerateRandom();
    Export(id_file);
  }
}

/// \brief Copy constructor. Creates an identity based on \a rht.
SMSpp::Identity::Identity(const Identity& rht)
  : m_params(new Botan::ECIES_System_Params(*rht.m_params))
{
  m_private_key = std::make_unique<PrivateKeyImpl>(
    (rht.m_private_key)->algorithm_identifier(),
    (rht.m_private_key)->private_key_bits()
  );

  m_public_key = std::make_unique<PublicKeyImpl>(
    m_private_key->algorithm_identifier(),
    m_private_key->public_key_bits()
  );
}

/// \brief Class destructor which uses the opportunity for zeroing keys.
SMSpp::Identity::~Identity()
{
  // take-over ownership
  PrivateKeyImpl* priv = m_private_key.release();
  PublicKeyImpl*   pub = m_public_key.release();

  // zeroing key memory space
  std::memset(reinterpret_cast<void*>(&priv), 0, sizeof(priv));
  std::memset(reinterpret_cast<void*>(&pub), 0, sizeof(pub));

  // pointer deletion
  delete priv;
  delete pub;
}

/// \brief Returns the fingerprint `SHA-256(pubkey)` for this identity.
std::string SMSpp::Identity::Fingerprint() const
{
  // prepares a hasher instance using SHA-256
  const auto hasher = Botan::HashFunction::create_or_throw("SHA-256");

  // executes SHA-256 hash function with bytes
  hasher->update(m_public_key->public_value());

  // creates digest and return as hexadecimal
  return Botan::hex_encode(hasher->final());
}

/// \brief Generates a random pair of ECDH private- and public-key.
void SMSpp::Identity::GenerateRandom()
{
  Botan::AutoSeeded_RNG rng;

  m_private_key = std::make_unique<PrivateKeyImpl>(
    rng, Botan::EC_Group("secp256r1")
  );

  m_public_key  = std::make_unique<PublicKeyImpl>(
    m_private_key->algorithm_identifier(),
    m_private_key->public_key_bits()
  );
}