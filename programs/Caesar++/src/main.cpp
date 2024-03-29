// src/main.cpp
#include <iostream>
#include <cryptopp/filters.h>
#include "caesar.h"

using CaesarCipher = CaesarPP::CaesarStreamTransformation;

int main()
{
  std::string input, cipher;
  CaesarCipher cipher_algo;

  std::cout << "Enter a message to encrypt: ";
  std::getline(std::cin, input);

  CryptoPP::StringSource source(input, true, new CryptoPP::StreamTransformationFilter(
    cipher_algo,
    new CryptoPP::StringSink(cipher)
  ));

  std::cout << "The Caesar Cipher is: "
            << cipher
            << std::endl;

  return 0;
}