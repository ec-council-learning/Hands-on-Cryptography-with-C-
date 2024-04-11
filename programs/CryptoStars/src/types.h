// src/types.h
#ifndef __CRYPTOSTARS_TYPES_H__
#define __CRYPTOSTARS_TYPES_H__

#include <string> // string
#include <map> // map
#include <vector> // vector

namespace CryptoStars {
  enum class Operation : char {
    Encrypt = 'e',
    Decrypt = 'd',
    Sign = 's',
    Verify = 'v',
    Channel = 'c'
  };

  using NamedKeyValueMap = std::map<std::string, std::string>;

  using ParametersList = std::vector<std::string>;

  using OperationsMap = std::map<Operation, std::string>;

}

#endif