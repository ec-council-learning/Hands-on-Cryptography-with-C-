// src/main.cpp
#include <iostream>
#include <memory>
#include "asymmetric.h"
#include "symmetric.h"
#include "benchmark.h"

using SymmetryRace::benchmark, SymmetryRace::AES, SymmetryRace::RSA;

int main()
{
  std::string ct_aes, ct_rsa;
  double elapsed_aes = 0, elapsed_rsa = 0;

  std::unique_ptr<AES> aes = std::make_unique<AES>();
  std::unique_ptr<RSA> rsa = std::make_unique<RSA>();

  benchmark(elapsed_aes, [&aes]() { return aes->generate_key(); });
  benchmark(elapsed_aes, [&aes, &ct_aes]() { return ct_aes = aes->encrypt("Hola!"); });
  benchmark(elapsed_aes, [&aes, ct_aes]() { return aes->decrypt(ct_aes); });

  benchmark(elapsed_rsa, [&rsa]() { return rsa->generate_key(); });
  benchmark(elapsed_rsa, [&rsa, &ct_rsa]() { return ct_rsa = rsa->encrypt("Hola!"); });
  benchmark(elapsed_rsa, [&rsa, ct_rsa]() { return rsa->decrypt(ct_rsa); });

  double min = std::min(elapsed_aes, elapsed_rsa);
  double max = std::max(elapsed_aes, elapsed_rsa);
  std::string winner = elapsed_aes < elapsed_rsa ? "AES" : "RSA";
  std::string loser  = elapsed_aes < elapsed_rsa ? "RSA" : "AES";

  std::cout << "The winner is: " << winner << "!" << std::endl
            << "Total time elapsed: " << min << "s (" << winner 
            << ") vs. " << max << "s (" << loser << ")" << std::endl;

  return 0;
}