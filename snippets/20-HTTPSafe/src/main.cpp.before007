// src/main.cpp
#include <iostream> // std::cout
#include <string> // std::string
#include <boost/asio.hpp> // boost::asio::io_context
#include "client.h"

int main(int argc, char* argv[])
{
  // 2 options required, e.g.: `HTTPSafe evi.as`
  auto flag = std::string(argv[1]);
  if (argc < 2 || flag == "-h" || flag == "help") {
    std::cout << "Usage: HTTPSafe [-h] <host>\n"
    return 1;
  }

  // parses command options
  const auto host = argv[1];

  try {

  }
  catch(std::exception& e) {
    std::cerr << "Error: " << e.what();
    return 1;
  }

  return 0;
}