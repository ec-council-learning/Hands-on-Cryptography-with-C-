// src/contact.h
#ifndef __WHISPERS_CONTACT_H__
#define __WHISPERS_CONTACT_H__
#include <memory> // std::unique_ptr
#include <string> // std::string
#include <vector> // std::vector
#include "identity.h" // Identity, PublicKeyImpl

namespace wiz {

  class Whisper;

  /// \brief Class implementation that describes contacts ("friends").
  class Contact {
    /// \brief Befriending class to be able to create shared secrets.
    friend class Whisper;

    /// \brief Contains the raw public key bytes.
    std::vector<uint8_t>            m_raw_public_key;

    /// \brief Contains an instance of Botan::ECDH_PublicKey.
    std::unique_ptr<wiz::PublicKeyImpl> m_public_key;

  public:
    /// \brief Constructs a contact from an Identity instance. 
    Contact(const Identity&);

    /// \brief Constructs a contact from a public key file (.wiz.pub).
    Contact(const std::string&);

    /// \brief Constructs a contact by copying another Contact instance.
    Contact(const Contact&);

    /// \brief Constructs a contact by moving another Contact instance.
    Contact(const Contact&&);

    /// \brief Default class destructor.
    virtual ~Contact() {}

    /// \brief Returns the fingerprint `SHA-256(pubkey)` for this contact.
    std::string Fingerprint() const;
  };

}
#endif