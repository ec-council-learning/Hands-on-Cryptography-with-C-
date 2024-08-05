// src/asymmetric.h
#ifndef __SYMMETRYRACE_ASYMMETRIC_H__
#define __SYMMETRYRACE_ASYMMETRIC_H__
#include "cipher.h"

namespace SymmetryRace {

  class AsymmetricCipher : public Cipher {
  public:
    AsymmetricCipher() : Cipher(32) {}
    AsymmetricCipher(size_t key_size) : Cipher(key_size) {}

    virtual std::string get_padding_scheme() const = 0;
    virtual std::string encrypt(std::string) const override;
    virtual std::string decrypt(std::string) const override;
  };

  class RSA : public AsymmetricCipher {
  public:
    RSA(): AsymmetricCipher(2048) {}
    RSA(size_t key_size) : AsymmetricCipher(key_size) {}
    virtual std::string get_padding_scheme() const override {
      return "OAEP(SHA-256)";
    }

    virtual std::string generate_key() override;
  };

}
#endif