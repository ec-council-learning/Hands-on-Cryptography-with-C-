// src/algorithm.h
#ifndef __CRYPTOSTARS_ALGORITHM_H__
#define __CRYPTOSTARS_ALGORITHM_H__

#include <string> // string
#include "types.h"// Operation, NamedKeyValueMap, ParametersList, OperationsMap

namespace CryptoStars {
  class Algorithm
  {
  protected:
    NamedKeyValueMap m_vargs;
    NamedKeyValueMap m_results;
    Operation m_op;

  public:
    std::string name;

    Algorithm(const std::string& n)
      : name(n)
    {}

    virtual ~Algorithm() {}

  // abstract API
    virtual int Compute() = 0;
    virtual OperationsMap GetOperations() const = 0;
    virtual ParametersList GetParameters(Operation) const = 0;

  // public API
    void SetParameters(NamedKeyValueMap args) { m_vargs = args; }
    void SetOperation(Operation o) { m_op = o; }
    NamedKeyValueMap GetResults() const { return m_results; }
  };
}

#endif