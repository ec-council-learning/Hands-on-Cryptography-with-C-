// src/rot13.h
#ifndef __CRYPTOSTARS_ROT13_H__
#define __CRYPTOSTARS_ROT13_H__

#include <string> // string
#include <vector> // vector
#include "algorithm.h" // Algorithm
#include "types.h" // Operation, ParametersList, OperationsMap

namespace CryptoStars {
  class ROT13 : public Algorithm
  {
  public:
    ROT13() : Algorithm("ROT13") {}

    int Compute() override;

    OperationsMap GetOperations() const override {
      return std::map<Operation, std::string>({
        { Operation::Encrypt, "(e)ncrypt - Encrypt a message" },
        { Operation::Decrypt, "(d)ecrypt - Decrypt a message" }
      });
    }

    ParametersList GetParameters(Operation op) const override {
      return std::vector<std::string>({ "message" });
    }
  };
}

#endif