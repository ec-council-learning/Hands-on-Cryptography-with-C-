// src/ui.h
#ifndef __CRYPTOSTARS_UI_H
#define __CRYPTOSTARS_UI_H

#include "algorithm.h" // Algorithm
#include "types.h" // Operation, NamedKeyValueMap

namespace CryptoStars::UI {

  using CryptoStars::Algorithm;
  using CryptoStars::Operation;
  using CryptoStars::NamedKeyValueMap;

  std::string AskForChoice(const std::string &, const std::vector<std::string>&);

  std::string AskForAlgorithm();

  Operation AskForOperation(Algorithm const&);

  NamedKeyValueMap AskForParameters(Operation, Algorithm const&);

  void DisplayResults(Algorithm const&);
}

#endif