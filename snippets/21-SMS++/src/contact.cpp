// src/contact.h
#include "contact.h"
#include <botan/x509_key.h> // Botan::X509::load_key
#include <botan/pk_keys.h> // Botan::Public_Key
#include <botan/hex.h> // Botan::hex_encode
#include <botan/hash.h> // Botan::HashFunction

/// \brief Constructs a contact from an Identity instance. 
SMSpp::Contact::Contact(const Identity& id)
{
  m_public_key = std::make_unique<SMSpp::PublicKeyImpl>(
    (id.m_public_key)->algorithm_identifier(),
    (id.m_public_key)->public_key_bits()
  );

  // also store content in raw format
  m_raw_public_key = m_public_key->public_value();
}

/// \brief Constructs a contact from a public key file (.smsid.pub).
SMSpp::Contact::Contact(const std::string& pub_file)
{
  Botan::DataSource_Stream input(pub_file); // non-binary mode (PEM)
  std::unique_ptr<Botan::Public_Key> pub = Botan::X509::load_key(input);

  m_public_key = std::make_unique<SMSpp::PublicKeyImpl>(
    pub->algorithm_identifier(),
    pub->public_key_bits()
  );

  // also store content in raw format
  m_raw_public_key = m_public_key->public_value();
}

/// \brief Constructs a contact by copying another Contact instance.
SMSpp::Contact::Contact(const Contact& rht)
  : m_raw_public_key(rht.m_raw_public_key),
    m_public_key(new SMSpp::PublicKeyImpl(*rht.m_public_key))
{}

/// \brief Constructs a contact by moving another Contact instance.
SMSpp::Contact::Contact(const Contact&& rht)
  : m_raw_public_key(std::move(rht.m_raw_public_key)),
    m_public_key(new SMSpp::PublicKeyImpl(*rht.m_public_key))
{}

/// \brief Returns the fingerprint `SHA-256(pubkey)` for this contact.
std::string SMSpp::Contact::Fingerprint() const
{
  // prepares a hasher instance using SHA-256
  const auto hasher = Botan::HashFunction::create_or_throw("SHA-256");

  // executes SHA-256 hash function with bytes
  hasher->update(m_raw_public_key);

  // creates digest and return as hexadecimal
  return Botan::hex_encode(hasher->final());
}