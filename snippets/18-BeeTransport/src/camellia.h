// src/camellia.h
#ifndef __BEETRANSPORT_CAMELLIA_H__
#define __BEETRANSPORT_CAMELLIA_H__
#include <string> // std::string
#include "flower.h" // Flower

namespace BeeTransport {
  class CamelliaBreed : public Flower {
  public:
    CamelliaBreed(size_t key_size) : Flower(key_size) {}
    CamelliaBreed(const std::string& key) : Flower(key) {}
    std::string name() const override;
    std::string encrypt(std::string) const override;
    std::string decrypt(std::string) const override;
    virtual std::string get_algorithm() const = 0;
  };

  class LargeCamellia : public CamelliaBreed {
  public:
    LargeCamellia() : CamelliaBreed(32) {}
    LargeCamellia(const std::string& key) : CamelliaBreed(key) {}
    std::string get_algorithm() const override { return "Camellia-256/CBC"; }
  };

  class MediumCamellia : public CamelliaBreed {
  public:
    MediumCamellia() : CamelliaBreed(24) {}
    MediumCamellia(const std::string& key) : CamelliaBreed(key) {}
    std::string get_algorithm() const override { return "Camellia-192/CBC"; }
  };

  class TinyCamellia : public CamelliaBreed {
  public:
    TinyCamellia() : CamelliaBreed(16) {}
    TinyCamellia(const std::string& key) : CamelliaBreed(key) {}
    std::string get_algorithm() const override { return "Camellia-128/CBC"; }
  };
}
#endif