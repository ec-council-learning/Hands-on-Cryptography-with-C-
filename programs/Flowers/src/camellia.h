// src/camellia.h
#ifndef __FLOWERS_CAMELLIA_H__
#define __FLOWERS_CAMELLIA_H__
#include <string> // std::string
#include "flower.h" // Flower

namespace Flowers {
  class CamelliaBreed : public Flower {
  public:
    CamelliaBreed(size_t key_size) : Flower(key_size) {}
    std::string encrypt(std::string) const override;
    std::string decrypt(std::string) const override;
    virtual std::string get_algorithm() const = 0;
  };

  class LargeCamellia : public CamelliaBreed {
  public:
    LargeCamellia() : CamelliaBreed(32) {}
    std::string get_algorithm() const override { return "Camellia-256/CBC"; }
  };

  class MediumCamellia : public CamelliaBreed {
  public:
    MediumCamellia() : CamelliaBreed(24) {}
    std::string get_algorithm() const override { return "Camellia-192/CBC"; }
  };

  class TinyCamellia : public CamelliaBreed {
  public:
    TinyCamellia() : CamelliaBreed(16) {}
    std::string get_algorithm() const override { return "Camellia-128/CBC"; }
  };
}
#endif