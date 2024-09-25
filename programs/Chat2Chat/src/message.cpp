// src/message.cpp
#include "message.h"
#include <string> // std::string
#include <vector> // std::vector
#include <botan/ecies.h> // Botan::ECIES_Encryptor
#include <botan/base64.h> // Botan::base64_encode
#include <botan/auto_rng.h> // Botan::AutoSeeded_RNG

c2c::Message::Message(
  const c2c::Identity& id,
  const c2c::Contact& to
) : m_id(id), m_friend(to)
{}

std::string c2c::Message::Handle(
  const std::string& command,
  const std::string& message
) const
{
  if (command == "read")
    return Read(message);

  return Write(message);
}

std::string c2c::Message::Read(const std::string& message) const
{
  Botan::AutoSeeded_RNG rng;

  // initializes the ECDH session using the recipient's private key
  // note: decryption can only happen using the "friend private key".
  Botan::ECIES_Decryptor  dec(*(m_id.m_private_key), *(m_id.m_params), rng);

  // expects base64 ciphertext
  Botan::secure_vector<uint8_t> bytes = Botan::base64_decode(message);

  // executes decryption operation
  Botan::secure_vector<uint8_t> plain = dec.decrypt(bytes);
  return std::string(plain.begin(), plain.end());
}

std::string c2c::Message::Write(const std::string& message) const
{
  Botan::AutoSeeded_RNG rng;

  // initializes the ECDH session (derives ephemeral private key)
  Botan::ECIES_Encryptor enc(*(m_id.m_private_key), *(m_id.m_params), rng);

  // ECDH companion (friend) public key
  enc.set_other_key((*m_friend.m_public_key).public_point());

  // executes encryption operation
  std::vector<uint8_t> bytes(message.begin(), message.end());
  std::vector<uint8_t> cipher = enc.encrypt(bytes, rng);

  // returns as base64
  return Botan::base64_encode(cipher);
}