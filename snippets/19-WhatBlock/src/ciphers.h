// src/ciphers.h
#ifndef __WHATBLOCK_CIPHERS_H__
#define __WHATBLOCK_CIPHERS_H__

#include <memory>
#include <type_traits>
#include "cipher.h"
#include "utils.h"

// block ciphers
#include "fixed.h" // DES, TripleDES, Blowfish, CASTS, IDEA, SHACAL2, Threefish
#include "dynamic.h" // AES<256>, ARIA<256>, Camellia<256>

namespace WhatBlock {
  std::unique_ptr<WhatBlock::Cipher> make_cipher(
    const std::string& algo
  ) {
    // creates a unique pointer to the parent class
    std::unique_ptr<WhatBlock::Cipher> cipher;
    std::string safe_user_choice = WhatBlock::strtolower(algo);

    if (std::string::npos != safe_user_choice.find("aria"))
      cipher = std::make_unique<WhatBlock::ARIA<256>>();
    else if (std::string::npos != safe_user_choice.find("blowfish"))
      cipher = std::make_unique<WhatBlock::Blowfish>();
    else if (std::string::npos != safe_user_choice.find("camellia"))
      cipher = std::make_unique<WhatBlock::Camellia<256>>();
    else if (std::string::npos != safe_user_choice.find("cast"))
      cipher = std::make_unique<WhatBlock::CASTS>();
    else if (std::string::npos != safe_user_choice.find("tripledes"))
      cipher = std::make_unique<WhatBlock::TripleDES>();
    else if (std::string::npos != safe_user_choice.find("des"))
      cipher = std::make_unique<WhatBlock::DES>();
    else if (std::string::npos != safe_user_choice.find("idea"))
      cipher = std::make_unique<WhatBlock::IDEA>();
    else if (std::string::npos != safe_user_choice.find("shacal"))
      cipher = std::make_unique<WhatBlock::SHACAL2>();
    else if (std::string::npos != safe_user_choice.find("threefish"))
      cipher = std::make_unique<WhatBlock::Threefish>();
    else
      cipher = std::make_unique<WhatBlock::AES<256>>();

    return /* std::move() */cipher;
  }
}

#endif