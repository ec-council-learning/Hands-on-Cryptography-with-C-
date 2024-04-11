// src/chacha20.cpp
#include <cryptopp/cryptlib.h> // byte, SecByteBlock
#include <cryptopp/chacha.h> // ChaChaTLS
#include <cryptopp/osrng.h> // AutoSeededRandomPool
#include "format.h" // bytes_to_hex, hex_to_bytes
#include "chacha20.h"

using CryptoPP::ChaChaTLS, CryptoPP::byte;
using CryptoStars::Format::bytes_to_hex;
using CryptoStars::Format::hex_to_bytes;

int CryptoStars::ChaCha20::Compute()
{
  // Computation cannot happen without a message
  if (m_vargs.end() == m_vargs.find("message")) {
    return 1;
  }

  // declares the input and output variables
  std::string input = m_vargs["message"],
              output;

  /* Operation::Encrypt */
  if (m_op == Operation::Encrypt) {
    return DoEncrypt(input);
  }

  /* Operation::Decrypt */
  std::string secretKey = m_vargs["secretKey"];
  return DoDecrypt(secretKey, input);
}

int CryptoStars::ChaCha20::DoEncrypt(const std::string& input)
{
  CryptoPP::AutoSeededRandomPool prng;
  std::string cipher, cipherHex;

  CryptoPP::SecByteBlock key(32), iv(12); // ChaChaTLS' iv length=12
  prng.GenerateBlock(key, key.size());
  prng.GenerateBlock(iv, iv.size());

  // creates the encryptor
  ChaChaTLS::Encryption enc;
  enc.SetKeyWithIV(key, key.size(), iv, iv.size());

  // performs the encryption
  cipher.resize(input.size());
  enc.ProcessData((byte*)&cipher[0], (const byte*) input.data(), input.size());

  m_results["ciphertext"] = bytes_to_hex(cipher);
  m_results["secretKey"] = bytes_to_hex(key) + bytes_to_hex(iv); // 32b || 12b
  return 0;
}

int CryptoStars::ChaCha20::DoDecrypt(
  const std::string& secretKey,
  const std::string& input
) {
  std::string plain;
  CryptoPP::byte key_bytes[ChaCha20::KEY_LENGTH],
                 iv_bytes[ChaCha20::IV_LENGTH],
                 input_bytes[input.length() / 2];

  // recovers the key and IV from the secret key
  // first 32 bytes of secretKey are from encryption key
  // last 12 bytes of secretKey are from input vector
  hex_to_bytes(&key_bytes[0], secretKey.substr(0, ChaCha20::KEY_LENGTH * 2));
  hex_to_bytes(&iv_bytes[0], secretKey.substr(ChaCha20::KEY_LENGTH * 2));

  // decodes the message from hex to binary
  hex_to_bytes(&input_bytes[0], input);

  // ChaChaTLS' key length=32, iv length=12
  CryptoPP::SecByteBlock key(key_bytes, 32), iv(iv_bytes, 12);

  // creates the decryptor
  ChaChaTLS::Decryption dec;
  dec.SetKeyWithIV(key, key.size(), iv, iv.size());

  // performs the decryption
  plain.resize(input.size());
  dec.ProcessData((byte*)&plain[0], input_bytes, input.length() / 2);

  m_results["plain"] = plain;
  return 0;
}