// src/ecdsa.h
#ifndef __CRYPTOSTARS_ECDSA_H__
#define __CRYPTOSTARS_ECDSA_H__
#include "algorithm.h"
#include "types.h"

namespace CryptoStars {
  class ECDSA : public Algorithm
  {
  public:
    ECDSA() : Algorithm("ECDSA") {}

    int Compute() override;

    OperationsMap GetOperations() const override {
      return std::map<Operation, std::string>({
        { Operation::Sign, "(s)ign - Sign a message" },
        { Operation::Verify, "(v)erify - Verify a signature" }
      });
    }

    ParametersList GetParameters(Operation op) const override {
      if (op == Operation::Sign) {
        return std::vector<std::string>({ "message" });
      }

      // Operation::Verify
      return std::vector<std::string>({ "message", "publicKey", "signature" });
    }

  protected:
    int DoSign(const std::string& input);
    int DoVerify(
      const std::string& publicKey,
      const std::string& input,
      const std::string& signature
    );
  };
}
#endif