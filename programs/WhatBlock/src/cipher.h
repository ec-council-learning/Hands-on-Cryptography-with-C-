// src/cipher.h
#ifndef __WHATBLOCK_CIPHER_H__
#define __WHATBLOCK_CIPHER_H__
#include <string> // std::string
#include <vector> // std::vector
#include <botan/auto_rng.h> // AutoSeeded_RNG
#include <botan/base64.h> // base64_encode

namespace WhatBlock {
  class Cipher
  {
  protected:
    size_t m_key_size;
    size_t m_block_size;
    std::string m_key;

  public:
    Cipher() : Cipher(/* key */32, /* block */16) {}
    Cipher(const std::string& key) : m_key(key) {}
    Cipher(const Cipher& f)
      : m_key(f.m_key), m_key_size(f.m_key_size), m_block_size(f.m_block_size)
    {}
    Cipher(size_t key_size, size_t block_size) {
      Botan::AutoSeeded_RNG rng;
      m_key = Botan::base64_encode(rng.random_vec(key_size));
      m_key_size = key_size;
      m_block_size = block_size;
    }
    virtual ~Cipher() {}

    std::string get_key() const { return m_key; }
    std::string encrypt(std::string) const;
    std::string decrypt(std::string) const;

    virtual std::string get_algorithm() const = 0;
  };
}
#endif