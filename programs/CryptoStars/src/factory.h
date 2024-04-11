// src/factory.h
#ifndef __CRYPTOSTARS_FACTORY_H__
#define __CRYPTOSTARS_FACTORY_H__

#include <memory> // unique_ptr, make_unique
#include "algorithm.h" // Algorithm
#include "aes.h" // AES
#include "rot13.h" // ROT13
#include "ecdsa.h" // ECDSA
#include "ecdh.h" // ECDH
#include "chacha20.h" // ChaCha20
#include "format.h" // strtolower

namespace CryptoStars {
  std::unique_ptr<CryptoStars::Algorithm> make_algorithm(
    const std::string& algo
  ) {
    // creates a unique pointer to the parent class
    std::unique_ptr<CryptoStars::Algorithm> algorithm;
    std::string safe_user_choice = CryptoStars::Format::strtolower(algo);

    // specializes the algorithm pointer with AES
    if (std::string::npos != safe_user_choice.find("aes")) {
      algorithm = std::make_unique<CryptoStars::AES>();
    }
    // specializes the algorithm pointer with ECDSA
    else if (std::string::npos != safe_user_choice.find("ecdsa")) {
      algorithm = std::make_unique<CryptoStars::ECDSA>();
    }
    // specializes the algorithm pointer with ECDH
    else if (std::string::npos != safe_user_choice.find("ecdh")) {
      algorithm = std::make_unique<CryptoStars::ECDH>();
    }
    // specializes the algorithm pointer with ChaCha20
    else if (std::string::npos != safe_user_choice.find("chacha20")) {
      algorithm = std::make_unique<CryptoStars::ChaCha20>();
    }
    // specializes the algorithm pointer with ROT13 (default)
    else {
      algorithm = std::make_unique<CryptoStars::ROT13>();
    }

    return /* std::move() */algorithm;
  }
}

#endif