// src/backend.h
#ifndef __HTTPSAFE_BACKEND_H__
#define __HTTPSAFE_BACKEND_H__
#include <botan/tls_client.h>
#include <botan/certstor_system.h>
#include <botan/credentials_manager.h>

namespace HTTPSafe {

  // Custom Credentials Manager to handle certificates
  class CredentialsManager : public Botan::Credentials_Manager
  {
  public:
    std::vector<Botan::Certificate_Store*> trusted_certificate_authorities(
      const std::string& type,
      const std::string& context) override
    {
      return { &system_cert_store }; // Use system CA store
    }

  private:
    Botan::System_Certificate_Store system_cert_store; // Default system certificate store
  };

  // Define a TLS policy
  class TLSPolicy : public Botan::TLS::Policy {
  public:
    bool acceptable_protocol_version(Botan::TLS::Protocol_Version version) const override {
      return version == Botan::TLS::Protocol_Version::TLS_V12;
    }
  };
}
#endif