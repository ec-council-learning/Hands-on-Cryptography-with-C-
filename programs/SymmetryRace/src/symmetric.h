// src/symmetric.h
#ifndef __SYMMETRYRACE_SYMMETRIC_H__
#define __SYMMETRYRACE_SYMMETRIC_H__
#include "cipher.h"

namespace SymmetryRace {

  class SymmetricCipher : public Cipher {
  public:
    SymmetricCipher() : Cipher(32) {}
    SymmetricCipher(size_t key_size) : Cipher(key_size) {}

    virtual std::string get_algorithm() const = 0;
    virtual std::string generate_key() override;
    virtual std::string encrypt(std::string) const override;
    virtual std::string decrypt(std::string) const override;
  };

  class AES : public SymmetricCipher {
  public:
    AES(): SymmetricCipher(32) {}
    virtual std::string get_algorithm() const override {
      return "AES-256/CBC";
    }
  };

}
#endif