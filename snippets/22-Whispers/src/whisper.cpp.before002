// src/whisper.cpp
#include "whisper.h"
#include <string> // std::string
#include <vector> // std::vector
#include <botan/ecies.h> // Botan::ECIES_Encryptor
#include <botan/base64.h> // Botan::base64_encode
#include <botan/auto_rng.h> // Botan::AutoSeeded_RNG

/// \brief Creates a new whisper with identity \a id and contact \a friend.
wiz::Whisper::Whisper(
  const wiz::Identity& id,
  const wiz::Contact& to
) : m_id(id), m_friend(to)
{}

/// \brief Handles a command \a command and passes it the input \a whisper.
std::string wiz::Whisper::Handle(
  const std::string& command,
  const std::string& whisper
) const
{
  if (command == "read")
    return Read(whisper);

  return Write(whisper);
}