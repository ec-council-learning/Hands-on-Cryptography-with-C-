// src/utils.h
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>
#include <iostream>
#include <iomanip>

namespace Randomizer {
namespace Utils {

  /// \brief Displays a SecByteBlock on the terminal (as hexadecimal)
  inline void print_buffer(CryptoPP::SecByteBlock buffer)
  {
    for (size_t i = 0, size = buffer.size(); i < size; i++)
    {
        std::cout << std::setbase(16) << std::setw(2) << std::setfill('0');
        std::cout << static_cast<unsigned int>(buffer[i]);
    }

    std::cout << std::endl;
  }

  /// \brief Displays a AES ciphertext on the terminal (as base64)
  inline void print_cipher(std::string cipher)
  {
    CryptoPP::StringSource encoder(cipher, true,  new CryptoPP::Base64Encoder(
      new CryptoPP::FileSink(std::cout)
    ));

    std::cout << std::endl;
  }

}
}