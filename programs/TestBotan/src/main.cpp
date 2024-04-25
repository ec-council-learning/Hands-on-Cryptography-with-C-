// src/main.cpp
#include <iostream>
#include <string>
#include "functions.h"

int main()
{
  std::string input;
  std::cout << "Enter a message to encrypt: ";
  std::getline(std::cin, input);

  std::cout << "Result of Serpent Encryption: " << encrypt(input) << std::endl;
  std::cout << "PEM Encoded secp256 Private Key: " << std::endl
            << pem_encoded_key();
  std::cout << "Whirlpool hash of user input: " << std::endl
            << whirlpool_hash(input) << std::endl;

  return 0;
}