// src/session.cpp
#include "session.h"

std::vector<Botan::Certificate_Store*>
Handshaker::UnsafeSession::trusted_certificate_authorities(
  const std::string& type,
  const std::string& context
) {
  BOTAN_UNUSED(type, context);
  return {&m_cert_store}; // uses systems CA store
}

std::vector<Botan::X509_Certificate> Handshaker::UnsafeSession::cert_chain(
  const std::vector<std::string>& cert_key_types,
  const std::vector<Botan::AlgorithmIdentifier>& cert_signature_schemes,
  const std::string& type,
  const std::string& context
) {
  BOTAN_UNUSED(cert_key_types, cert_signature_schemes, type, context);
  return {}; // empty = unauthenticated client session
}

std::shared_ptr<Botan::Private_Key> Handshaker::UnsafeSession::private_key_for(
  const Botan::X509_Certificate& cert,
  const std::string& type,
  const std::string& context
) {
  BOTAN_UNUSED(cert, type, context);
  return nullptr; // empty = unauthenticated client session
}