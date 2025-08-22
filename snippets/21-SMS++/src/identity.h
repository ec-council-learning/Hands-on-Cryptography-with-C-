// src/identity.h
#ifndef __SMSPLUSPLUS_IDENTITY_H__
#define __SMSPLUSPLUS_IDENTITY_H__
#include <memory> // std::unique_ptr
#include <string> // std::string
#include <botan/ecdh.h> // ECDH_PrivateKey, ECDH_PublicKey
#include <botan/ecies.h> // ECIES_System_Params

namespace SMSpp {
  typedef Botan::ECDH_PrivateKey PrivateKeyImpl;
  typedef Botan::ECDH_PublicKey   PublicKeyImpl;
  class Message;

  /// \brief Class implementation that describes identities (private).
  class Identity final
  {
    friend class Message;
    std::unique_ptr<PrivateKeyImpl>        m_private_key;
    std::unique_ptr<Botan::ECIES_System_Params> m_params;
  public:
    std::unique_ptr<PublicKeyImpl>          m_public_key;

    Identity(const std::string&);
    Identity(const Identity&);
    virtual ~Identity();

    std::string Fingerprint() const;
  private:
    void            GenerateRandom();
    const Identity& Import(const std::string&);
    void            Export(const std::string&) const;
  };
}
#endif