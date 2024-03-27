// src/main.cpp
#include <iostream>
#include <string>
#include <cryptopp/default.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>

int main()
{
  std::string input, cipher, cipher_b64, cipher_s256;
  CryptoPP::SHA256 hash;

  std::cout << "Enter a message to encrypt: ";
  std::getline(std::cin, input);

  // encrypt
  CryptoPP::StringSource enc_source(input, true, new CryptoPP::DefaultEncryptor(
    "NotSoSecurePassword",
    new CryptoPP::StringSink(cipher)
  ));

  // base64-encode
  CryptoPP::StringSource b64_source(cipher, true,  new CryptoPP::Base64Encoder(
    new CryptoPP::StringSink(cipher_b64)
  ));

  // SHA-256 hash algorithm
  CryptoPP::StringSource source(input, true, new CryptoPP::HashFilter(
    hash,
    new CryptoPP::HexEncoder(new CryptoPP::StringSink(cipher_s256))
  ));

  std::cout << "Result of AES Encryption: "
            << cipher_b64
            << std::endl;

  std::cout << "Result of SHA-256 Hashes: "
            << cipher_s256
            << std::endl;

  return 0;
}