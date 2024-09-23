// src/fixed.h
#ifndef __WHATBLOCK_FIXED_H__
#define __WHATBLOCK_FIXED_H__
#include "cipher.h"

namespace WhatBlock {
  class DES : public Cipher {
  public:
    DES() : Cipher(8, 8) {}
    std::string get_algorithm() const override {
      return "DES/CBC";
    }
  };

  class TripleDES : public Cipher {
  public:
    TripleDES() : Cipher(24, 8) {}
    std::string get_algorithm() const override {
      return "TripleDES/CBC";
    }
  };
  
  class Blowfish : public Cipher {
  public:
    Blowfish() : Cipher(8, 8) {}
    std::string get_algorithm() const override {
      return "Blowfish/CBC";
    }
  };

  class Threefish : public Cipher {
  public:
    Threefish() : Cipher(64, 64) {}
    std::string get_algorithm() const override {
      return "Threefish-512/CBC";
    }
  };

  class CASTS : public Cipher {
  public:
    CASTS() : Cipher(16, 8) {}
    std::string get_algorithm() const override {
      return "CAST-128/CBC";
    }
  };

  class IDEA : public Cipher {
  public:
    IDEA() : Cipher(16, 8) {}
    std::string get_algorithm() const override {
      return "IDEA/CBC";
    }
  };

  class SHACAL2 : public Cipher {
  public:
    SHACAL2() : Cipher(64, 32) {}
    std::string get_algorithm() const override {
      return "SHACAL2/CBC";
    }
  };
}

#endif