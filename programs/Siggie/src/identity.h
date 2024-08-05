// src/identity.h
#ifndef __SIGGIE_IDENTITY_H__
#define __SIGGIE_IDENTITY_H__

#include <string> // std::string
#include <filesystem> // std::filesystem
#include <stdexcept> // std::runtime_error
#include <botan/ecdsa.h> // ECDSA_PrivateKey, ECDSA_PublicKey

namespace Siggie {

  using PrivateKeyImpl = Botan::ECDSA_PrivateKey;
  using PublicKeyImpl = Botan::ECDSA_PublicKey;

  /// \brief Class for identities that consist of an ECDSA private/public keypair.
  class Identity
  {
    std::unique_ptr<PrivateKeyImpl> m_private_key;

  public:
    std::unique_ptr<PublicKeyImpl>  m_public_key;

    /// \brief Default constructor. Creates an ECDSA identity for EC domain secp256r1.
    Identity();

    /// \brief Creates an identity with file \a filename and pass \a passphrase.
    Identity(const std::string&, const std::string&);

    /// \brief Copy constructor. Creates an identity based on the other's private key.
    Identity(const Identity&);

    /// \brief Default class destructor. Uses the opportunity for zeroing keys.
    virtual ~Identity();

    /// \brief Saves the private key to file \a filename with password \a passphrase.
    void Export(const std::string&, const std::string&) const;

    /// \brief Exports the private key instance for use outside of the class.
    /// \note  Caution: It is not recommended to permit this operation.
    std::unique_ptr<PrivateKeyImpl> ExportPrivateKey() const;

    /// \brief Exports the public key instance for use outside of the class.
    std::unique_ptr<PublicKeyImpl> ExportPublicKey() const;
  };

  /// \brief Creates a new random ECDSA identity.
  inline std::unique_ptr<Identity> make_identity() {
    return std::make_unique<Identity>();
  }

  /// \brief Creates an ECDSA identity from file \a file with password \a pass.
  inline std::unique_ptr<Identity> make_identity(
    const std::string& file,
    const std::string& pass
  ) {
    std::filesystem::directory_entry entry{file};
    if (! entry.exists())
      throw std::runtime_error("Error: Identity file does not exist.");

    return std::make_unique<Identity>(file, pass);
  }

}

#endif