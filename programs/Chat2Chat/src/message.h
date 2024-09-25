// src/message.h
#ifndef __CHAT2CHAT_MESSAGE_H__
#define __CHAT2CHAT_MESSAGE_H__
#include <string> // std::string
#include "identity.h"
#include "contact.h"

namespace c2c {

  class Identity;

  /// \brief Class implementation that describes ECIES-encrypted messages.
  class Message
  {
    /// \brief The sender Identity instance, its private key must be set.
    const Identity&   m_id;

    /// \brief The recipient Contact instance, its public key must be set.
    const Contact& m_friend;

  public:
    /// \brief Creates a new message with identity \a id and contact \a friend.
    Message(
      const Identity&,
      const Contact&
    );

    /// \brief Default class destructor.
    virtual ~Message() {};

    /// \brief Handles a command \a command and passes it the input \a message.
    std::string Handle(const std::string&, const std::string&) const;

  private:
    /// \brief Decrypts a ciphertext \a message, encrypted by a friend.
    std::string Read(const std::string&) const;

    /// \brief Encrypts a plaintext \a message destined at a friend.
    std::string Write(const std::string&) const;
  };
}
#endif