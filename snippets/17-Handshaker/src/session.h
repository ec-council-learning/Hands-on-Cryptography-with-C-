// src/session.h
#ifndef __HANDSHAKER_SESSION_H__
#define __HANDSHAKER_SESSION_H__
#include <string> // std::string
#include <vector> // std::vector
#include <memory> // std::shared_ptr
#include <botan/certstor.h> // Certificate_Store
#include <botan/certstor_system.h> // System_Certificate_Store
#include <botan/tls.h> // Credentials_Manager

namespace Handshaker {
  /// \brief A credentials manager that does *not* require client authentication.
  class UnsafeSession : public Botan::Credentials_Manager
  {
  private:
    Botan::System_Certificate_Store m_cert_store;

  public:
    /// \brief Return a list of certificates of CAs we trust for tls server certificates
    std::vector<Botan::Certificate_Store*> trusted_certificate_authorities(
      const std::string& type, const std::string& context
    );

    /// \brief Returns a certificate chain being sent to the tls server (optional)
    std::vector<Botan::X509_Certificate> cert_chain(
      const std::vector<std::string>& cert_key_types,
      const std::vector<Botan::AlgorithmIdentifier>& cert_signature_schemes,
      const std::string& type, const std::string& context
    );

    /// \brief Returns the private key associated with the leaf certificate
    std::shared_ptr<Botan::Private_Key> private_key_for(
      const Botan::X509_Certificate& cert,
      const std::string& type, const std::string& context
    );
  };
}
#endif