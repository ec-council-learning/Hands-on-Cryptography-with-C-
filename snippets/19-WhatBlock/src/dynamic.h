// src/dynamic.h
#ifndef __WHATBLOCK_DYNAMIC_H__
#define __WHATBLOCK_DYNAMIC_H__
#include "cipher.h"

namespace WhatBlock {
  template <unsigned int nBits = 256>
  class AES : public Cipher {
  public:
    AES() : Cipher(nBits/8, 16) {}
    std::string get_algorithm() const override {
      return "AES-" + std::to_string(nBits) + "/GCM";
    }
  };

  typedef AES<256> AES256;
  typedef AES<192> AES192;
  typedef AES<128> AES128;

  template <unsigned int nBits = 256>
  class ARIA : public Cipher {
  public:
    ARIA() : Cipher(nBits/8, 16) {}
    std::string get_algorithm() const override {
      return "ARIA-" + std::to_string(nBits) + "/GCM";
    }
  };

  typedef ARIA<256> ARIA256;
  typedef ARIA<192> ARIA192;
  typedef ARIA<128> ARIA128;

  template <unsigned int nBits = 256>
  class Camellia : public Cipher {
  public:
    Camellia() : Cipher(nBits/8, 16) {}
    std::string get_algorithm() const override {
      return "Camellia-" + std::to_string(nBits) + "/GCM";
    }
  };

  typedef Camellia<256> Camellia256;
  typedef Camellia<192> Camellia192;
  typedef Camellia<128> Camellia128;
}

#endif