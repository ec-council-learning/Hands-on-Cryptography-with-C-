// src/utils.h
#ifndef __WHATBLOCK_UTILS_H__
#define __WHATBLOCK_UTILS_H__

#include <iostream> // std::cout
#include <algorithm> // std::transform
#include <vector> // std::vector
#include <string> // std::string

namespace WhatBlock {
  /// \brief Returns the lowercase transformed string
  std::string strtolower(const std::string& input)
  {
    std::string output;
    output.resize(input.size());

    std::transform(input.begin(), input.end(), output.begin(),
        [](unsigned char c){ return std::tolower(c); });
    return output;
  }

  std::string ask_input_choices(
    const std::string &message,
    const std::vector<std::string>& choices
  ) {
    std::string choice;
    std::cout << message << std::endl << std::endl;
    for (auto c: choices)
      std::cout << c << std::endl;
    std::cout << std::endl << "Choose one of the above: ";
    std::getline(std::cin, choice);
    std::cout << std::endl;
    return choice;
  }
}

#endif