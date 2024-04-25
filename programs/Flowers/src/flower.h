// src/flower.h
#ifndef __FLOWERS_FLOWER_H__
#define __FLOWERS_FLOWER_H__
#include <string> // std::string
#include <vector> // std::vector
#include <botan/auto_rng.h> // AutoSeeded_RNG
#include <botan/base64.h> // base64_encode

namespace Flowers {
  class Flower
  {
  protected:
    std::string m_key;

  public:
    Flower() : Flower(32) {}
    Flower(const std::string& key) : m_key(key) {}
    Flower(size_t key_size) {
      Botan::AutoSeeded_RNG rng;
      m_key = Botan::base64_encode(rng.random_vec(key_size));
    }
    virtual ~Flower() {}

    std::string get_seed() const { return m_key; }
    virtual std::string encrypt(std::string) const = 0;
    virtual std::string decrypt(std::string) const = 0;
  };
}
#endif