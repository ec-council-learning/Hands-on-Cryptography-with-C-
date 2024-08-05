// src/cipher.h
#ifndef __SYMMETRYRACE_CIPHER_H__
#define __SYMMETRYRACE_CIPHER_H__
#include <string> // std::string
#include <vector> // std::vector

namespace SymmetryRace {
  class Cipher
  {
  protected:
    size_t m_key_size;
    std::string m_key;

  public:
    Cipher() : Cipher(/* key */32) {}
    Cipher(const std::string& key) : m_key(key) {}
    Cipher(const Cipher& f)
      : m_key(f.m_key), m_key_size(f.m_key_size)
    {}
    Cipher(size_t key_size) {
      m_key_size = key_size;
      m_key = "";
    }
    virtual ~Cipher() {}

    std::string get_key() const { return m_key; }

    virtual std::string generate_key() = 0;
    virtual std::string encrypt(std::string) const = 0;
    virtual std::string decrypt(std::string) const = 0;
  };
}
#endif