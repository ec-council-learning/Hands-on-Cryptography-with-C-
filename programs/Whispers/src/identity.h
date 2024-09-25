// src/identity.h
#ifndef __WHISPERS_IDENTITY_H__
#define __WHISPERS_IDENTITY_H__
#include <memory> // std::unique_ptr
#include <string> // std::string
#include <botan/ecdh.h> // ECDH_PrivateKey, ECDH_PublicKey
#include <botan/ecies.h> // ECIES_System_Params

namespace wiz {

  /// \brief Type used to describe an identity's private key instance.
  typedef Botan::ECDH_PrivateKey PrivateKeyImpl;

  /// \brief Type used to describe an identity's public key instance.
  typedef Botan::ECDH_PublicKey  PublicKeyImpl;

  class Whisper;

  /// \brief Class implementation that describes identities (private).
  class Identity final
  {
    /// \brief Befriending class to be able to create shared secrets.
    friend class Whisper;

    /// \brief Contains a unique pointer to the private key implementation.
    /// \note This member variable is wiped-out ("zero'd") by the destructor.
    std::unique_ptr<PrivateKeyImpl> m_private_key;

    /// \brief Contains the parameters for the ECIES algorithms.
    std::unique_ptr<Botan::ECIES_System_Params> m_params;

  public:
    /// \brief Contains a unique pointer to the public key implementation.
    /// \note This member variable is wiped-out ("zero'd") by the destructor.
    std::unique_ptr<PublicKeyImpl>  m_public_key;

    /// \brief Default constructor. Creates and initializes an ECDH identity
    ///        using the \a id_file identity file if it exists, or creates a
    ///        random ECDH private key if the file doesn't exist.
    Identity(const std::string&);

    /// \brief Copy constructor. Creates an identity based on \a rht.
    Identity(const Identity&);

    /// \brief Class destructor which uses the opportunity for zeroing keys.
    virtual ~Identity();

    /// \brief Returns the fingerprint `SHA-256(pubkey)` for this identity.
    std::string Fingerprint() const;

    /// \brief Returns the string representation of an Identity (public key).
    operator std::string() const;

  private:
    /// \brief Generates a random pair of ECDH private- and public-key.
    void GenerateRandom();

    /// \brief Creates an identity with file \a filename and an empty passphrase.
    const Identity& Import(const std::string&);

    /// \brief Saves an identity to file \a filename using an empty passphrase.
    void Export(const std::string&) const;
  };

}
#endif