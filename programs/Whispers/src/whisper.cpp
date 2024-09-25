// src/whisper.cpp
#include "whisper.h"
#include <string> // std::string
#include <vector> // std::vector
#include <botan/ecies.h> // Botan::ECIES_Encryptor
#include <botan/base64.h> // Botan::base64_encode
#include <botan/auto_rng.h> // Botan::AutoSeeded_RNG

wiz::Whisper::Whisper(
  const wiz::Identity& id,
  const wiz::Contact& to
) : m_id(id), m_friend(to)
{}

std::string wiz::Whisper::Handle(
  const std::string& command,
  const std::string& whisper
) const
{
  if (command == "read")
    return Read(whisper);

  return Write(whisper);
}

std::string wiz::Whisper::Read(const std::string& whisper) const
{
  Botan::AutoSeeded_RNG rng;

  // initializes the ECDH session using the recipient's private key
  // note: decryption can only happen using the "friend private key".
  Botan::ECIES_Decryptor  dec_pk(*(m_id.m_private_key), *(m_id.m_params), rng);
  Botan::ECIES_Decryptor  dec_full(*(m_id.m_private_key), *(m_id.m_params), rng);

  // expects base64 ciphertext
  Botan::secure_vector<uint8_t> allbytes = Botan::base64_decode(whisper);

  // (1): decrypts the IV and encrypted bytes using private key
  Botan::secure_vector<uint8_t> bytes = dec_pk.decrypt(allbytes);

  // first 16 bytes contain the IV (now decrypted)
  auto iv = Botan::secure_vector<uint8_t>(bytes.begin(), bytes.begin()+16);
  dec_full.set_initialization_vector(Botan::OctetString(iv));

  // rest is the whisper ciphertext (encrypted with pk and iv)
  auto cipher = Botan::secure_vector<uint8_t>(bytes.begin()+16, bytes.end());

  // (2): decrypts the whisper using IV and private key
  Botan::secure_vector<uint8_t> plain = dec_full.decrypt(cipher);
  return std::string(plain.begin(), plain.end());
}

std::string wiz::Whisper::Write(const std::string& whisper) const
{
  Botan::AutoSeeded_RNG rng;

  // initializes the ECDH session (derives ephemeral private key)
  Botan::ECIES_Encryptor enc_pk(*(m_id.m_private_key), *(m_id.m_params), rng);
  Botan::ECIES_Encryptor enc_full(*(m_id.m_private_key), *(m_id.m_params), rng);

  // ECDH companion (friend) public key
  enc_pk.set_other_key((*m_friend.m_public_key).public_point());
  enc_full.set_other_key((*m_friend.m_public_key).public_point());

  // random encryption seed (16 bytes IV) on a per-message basis
  auto iv = Botan::OctetString(rng, 16);
  enc_full.set_initialization_vector(iv);

  // (1): encrypts the message using IV and private key ("full")
  std::vector<uint8_t> wbytes(whisper.begin(), whisper.end());
  std::vector<uint8_t> wcipher = enc_full.encrypt(wbytes, rng);

  // prepends the IV to the encrypted bytes of the whisper
  std::vector<uint8_t> bytes(wcipher.begin(), wcipher.end());
  bytes.insert(bytes.begin(), iv.begin(), iv.end());

  // (2): encrypts the IV and encrypted bytes using private key
  // note: this permits to later decrypt the IV with private key
  std::vector<uint8_t> cipher = enc_pk.encrypt(bytes, rng);

  // returns as base64
  return Botan::base64_encode(cipher);
}