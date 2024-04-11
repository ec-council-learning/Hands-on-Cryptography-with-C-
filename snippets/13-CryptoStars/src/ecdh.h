// src/ecdh.h
#ifndef __CRYPTOSTARS_ECDH_H__
#define __CRYPTOSTARS_ECDH_H__

#include <string> // string
#include <vector> // vector
#include "algorithm.h" // Algorithm
#include "types.h" // Operation, ParametersList, OperationsMap

namespace CryptoStars {
  class ECDH : public Algorithm
  {
  public:
    ECDH() : Algorithm("ECDH") {}

    int Compute() override;

    OperationsMap GetOperations() const override {
      return std::map<Operation, std::string>({
        { Operation::Channel, "(c)hannel - Create a shared secret" }
      });
    }

    ParametersList GetParameters(Operation op) const override {
      return std::vector<std::string>({});
    }
  };
}

#endif