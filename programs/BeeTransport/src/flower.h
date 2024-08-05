// src/flower.h
#ifndef __BEETRANSPORT_FLOWER_H__
#define __BEETRANSPORT_FLOWER_H__
#include <string> // std::string
#include <vector> // std::vector
#include <botan/auto_rng.h> // AutoSeeded_RNG
#include <botan/base64.h> // base64_encode

namespace BeeTransport {
  class Flower
  {
  protected:
    size_t m_size;
    std::string m_key;
    std::string m_bud;

  public:
    bool has_breed = false;

    Flower() : Flower(32) {}
    Flower(const std::string& key) : m_key(key) { m_bud = reproduce(); }
    Flower(size_t key_size) {
      Botan::AutoSeeded_RNG rng;
      m_key = Botan::base64_encode(rng.random_vec(key_size));
      m_bud = reproduce();
    }

    /// \brief Adds copy construction operator
    Flower(const Flower& f)
      : m_key(f.m_key), m_bud(f.m_bud), m_size(f.m_size), has_breed(f.has_breed)
    {}

    virtual ~Flower() {}

    std::string get_seed() const { return m_key; }
    std::string get_bud() const { return m_bud; }
    virtual std::string name() const = 0;
    virtual std::string encrypt(std::string) const = 0;
    virtual std::string decrypt(std::string) const = 0;

  private:
    std::string reproduce();
  };
}
#endif