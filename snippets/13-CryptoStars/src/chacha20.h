// src/chacha20.h
#ifndef __CRYPTOSTARS_CHACHA20_H__
#define __CRYPTOSTARS_CHACHA20_H__
#include <string> // std::string
#include <vector> // std::vector
#include "algorithm.h" // Algorithm
#include "types.h" // Operation, ParametersList, OperationsMap

namespace CryptoStars {
  class ChaCha20 : public Algorithm
  {
  public:
    const unsigned int KEY_LENGTH = 32;
    const unsigned int IV_LENGTH = 12;

    ChaCha20() : Algorithm("ChaCha20") {}

    int Compute() override;

    OperationsMap GetOperations() const override {
      return std::map<Operation, std::string>({
        { Operation::Encrypt, "(e)ncrypt - Encrypt a message" },
        { Operation::Decrypt, "(d)ecrypt - Decrypt a message" }
      });
    }

    ParametersList GetParameters(Operation op) const override {
      if (op == Operation::Encrypt) {
        return std::vector<std::string>({ "message" });
      }
      // Operation::Decrypt
      return std::vector<std::string>({ "message", "secretKey" });
    }

  protected:
    int DoEncrypt(const std::string& input);
    int DoDecrypt(const std::string& secretKey, const std::string& input);
  };
}
#endif