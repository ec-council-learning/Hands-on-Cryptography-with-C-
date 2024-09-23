// src/main.cpp
#include <iostream>
#include "utils.h"
#include "ciphers.h"

int main(int argc, char* argv[])
{
  std::string cipher_opt = argc >= 2 ? std::string(argv[1]) : "",
              choice;

  if (!cipher_opt.empty())
    choice = cipher_opt;
  else {
    choice = WhatBlock::ask_input_choices(
      "Which block cipher would you like to use today? ",
      {
        "AES-256       - Use the popular Advanced Encryption Standard",
        "ARIA-256      - Use the South Korean block cipher Standard",
        "Camellia-256  - Use the popular NESSIE Standard block cipher",
        "Blowfish      - Use the pre-AES popular Blowfish standard",
        "CAST-128      - Use the OpenPGP-featured block cipher (CASTS)",
        "DES           - Use the Data Encryption Standard (caution!)",
        "TripleDES     - Use the Triple Data Encryption Standard",
        "IDEA          - Use the PGP-featured block cipher IDEA",
        "SHACAL2       - Use the SHA-256-featured block cipher",
        "Threefish-512 - Use the tweakable block cipher Threefish"
      }
    );
  }

  // creates a unique pointer to the parent class
  // and the factory creates the child class instance
  std::unique_ptr<WhatBlock::Cipher> cipher;
  cipher = WhatBlock::make_cipher(choice);

  std::string encrypted_full = cipher->encrypt("Hello, World!"),
              decrypted_full = cipher->decrypt(encrypted_full);

  std::cout << "Encrypting with " << cipher->get_algorithm();
  std::cout << std::endl <<  encrypted_full << std::endl;

  std::cout << std::endl <<  "Decrypts to: "
            << decrypted_full << std::endl;
  return 0;
}