// src/contact.h
#include "contact.h"
#include <botan/x509_key.h> // Botan::X509::load_key
#include <botan/pk_keys.h> // Botan::Public_Key
#include <botan/hex.h> // Botan::hex_encode
#include <botan/hash.h> // Botan::HashFunction

wiz::Contact::Contact(const Identity& id)
{
  m_public_key = std::make_unique<wiz::PublicKeyImpl>(
    (id.m_public_key)->algorithm_identifier(),
    (id.m_public_key)->public_key_bits()
  );

  // also store content in raw format
  m_raw_public_key = m_public_key->public_value();
}

wiz::Contact::Contact(const std::string& pub_file)
{
  Botan::DataSource_Stream input(pub_file); // non-binary mode (PEM)
  std::unique_ptr<Botan::Public_Key> pub = Botan::X509::load_key(input);

  m_public_key = std::make_unique<wiz::PublicKeyImpl>(
    pub->algorithm_identifier(),
    pub->public_key_bits()
  );

  // also store content in raw format
  m_raw_public_key = m_public_key->public_value();
}

wiz::Contact::Contact(const Contact& rht)
  : m_raw_public_key(rht.m_raw_public_key),
    m_public_key(new wiz::PublicKeyImpl(*rht.m_public_key))
{}

wiz::Contact::Contact(const Contact&& rht)
  : m_raw_public_key(std::move(rht.m_raw_public_key)),
    m_public_key(new wiz::PublicKeyImpl(*rht.m_public_key))
{}

std::string wiz::Contact::Fingerprint() const
{
  // prepares a hasher instance using SHA-256
  const auto hasher = Botan::HashFunction::create_or_throw("SHA-256");

  // executes SHA-256 hash function with bytes
  hasher->update(m_raw_public_key);

  // creates digest and return as hexadecimal
  return Botan::hex_encode(hasher->final());
}