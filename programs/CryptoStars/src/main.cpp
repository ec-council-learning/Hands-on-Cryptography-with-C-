// src/main.cpp
#include <string> // string
#include <memory> // unique_ptr
#include "ui.h" // UI
#include "algorithm.h" // Algorithm
#include "factory.h" // make_algorithm
#include "types.h" // NamedKeyValueMap

using CryptoStars::UI::AskForAlgorithm,
      CryptoStars::UI::AskForOperation,
      CryptoStars::UI::AskForParameters,
      CryptoStars::UI::DisplayResults,
      CryptoStars::NamedKeyValueMap;

int main()
{
  // uses iostream to ask for an algorithm name
  std::string algo = AskForAlgorithm();

  // creates a unique pointer to the parent class
  // and the factory creates the child class instance
  std::unique_ptr<CryptoStars::Algorithm> algorithm;
  algorithm = CryptoStars::make_algorithm(algo);

  // uses iostream to ask for an operation
  CryptoStars::Operation op = AskForOperation(*algorithm);
  algorithm->SetOperation(op);

  // asks for protocol parameters with iostream
  NamedKeyValueMap parameters = AskForParameters(op, *algorithm);
  algorithm->SetParameters(parameters);

  // executes the underlying algorithm
  unsigned int result = algorithm->Compute();
  DisplayResults(*algorithm);

  return result; // 0 = Success
}