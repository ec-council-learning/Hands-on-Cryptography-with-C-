// src/whisper.h
#ifndef __WHISPERS_WHISPER_H__
#define __WHISPERS_WHISPER_H__
#include <string> // std::string
#include "identity.h"
#include "contact.h"

namespace wiz {

  class Identity;

  /// \brief Class implementation that describes ECIES-encrypted whispers.
  class Whisper
  {
    /// \brief The sender Identity instance, its private key must be set.
    const Identity&   m_id;

    /// \brief The recipient Contact instance, its public key must be set.
    const Contact& m_friend;

  public:
    /// \brief Creates a new whisper with identity \a id and contact \a friend.
    Whisper(
      const Identity&,
      const Contact&
    );

    /// \brief Default class destructor.
    virtual ~Whisper() {};

    /// \brief Handles a command \a command and passes it the input \a whisper.
    std::string Handle(const std::string&, const std::string&) const;

  private:
    /// \brief Decrypts a ciphertext \a whisper, encrypted by a friend.
    std::string Read(const std::string&) const;

    /// \brief Encrypts a plaintext \a whisper destined at a friend.
    std::string Write(const std::string&) const;
  };
}
#endif