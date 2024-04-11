// src/ui.cpp
#include <iostream> // cout, cin, getline
#include "format.h" // map_to_vector
#include "ui.h"

using CryptoStars::Algorithm;
using CryptoStars::Operation;
using CryptoStars::NamedKeyValueMap;
using CryptoStars::Format::map_to_vector;

std::string CryptoStars::UI::AskForChoice(
  const std::string &message,
  const std::vector<std::string>& choices
) {
  std::string choice;
  std::cout << message << std::endl << std::endl;
  for (auto c: choices)
    std::cout << c << std::endl;
  std::cout << std::endl << "Choose one of the above: ";
  std::getline(std::cin, choice);
  return choice;
}

std::string CryptoStars::UI::AskForAlgorithm()
{
  return AskForChoice("Which algorithm would you like to use today? ",
    {
      "AES       - Use the popular Advanced Encryption Standard",
      "ECDSA     - Sign documents with elliptic-curve cryptography",
      "ECDH      - Use the Ellitic Curve Diffie-Hellman key agreement",
      "ChaCha20  - Encryption that is consistently faster than AES",
      "ROT13     - Encryption  using the popular ROT13 algorithm"
    }
  );
}

Operation CryptoStars::UI::AskForOperation(Algorithm const& algorithm)
{
  CryptoStars::OperationsMap ops = algorithm.GetOperations();
  std::vector<std::string> choices;
  map_to_vector(ops, choices);

  std::string op = AskForChoice("Which operation would you like to execute? ",
    choices
  );

  // passes only one character
  return static_cast<Operation>(op.at(0));
}

NamedKeyValueMap CryptoStars::UI::AskForParameters(
  Operation op,
  Algorithm const& algorithm
) {
  ParametersList arguments = algorithm.GetParameters(op);
  if (0 == arguments.size())
    return NamedKeyValueMap();

  NamedKeyValueMap parameters;
  for (auto param : arguments) {
    // asks for parameters in terminal
    std::string input;
    std::cout << "Enter a " << param << ": ";
    std::getline(std::cin, input);

    // registers parameter for computation
    parameters[param] = input;
  }

  return parameters;
}

void CryptoStars::UI::DisplayResults(Algorithm const& algorithm)
{
  std::cout << std::endl << "Results of " << algorithm.name << ": " << std::endl;
  for (auto pair : algorithm.GetResults())
    std::cout << pair.first << " = " << pair.second << std::endl;
}