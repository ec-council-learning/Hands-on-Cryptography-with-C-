// src/main.cpp
#include <iostream> // std::cout
#include <string> // std::string
#include <boost/asio.hpp>
#include "client.h"

int print_usage() {
  std::cout
    << "Usage: HTTPSafe [-h] <host>\n"
    << "  e.g: HTTPSafe evi.as:443\n"
    << "  e.g: HTTPSafe example.com\n"
    << "\nFLAGS: \n"
    << "  -h: Prints this help message and usage examples.\n";
  return 1;
}

int main(int argc, char* argv[])
{
  // 2 options required, e.g.: `HTTPSafe evi.as`
  // also accepted are: `HTTPSafe -h` and `HTTPSafe help`
  auto flag = std::string(argv[1]);
  if (argc < 2 || flag == "-h" || flag == "help")
    return print_usage();

  // parses command options
  const auto host = argv[1];

  try {
    // Initialize Boost.Asio I/O context
    boost::asio::io_context io_context;

    // Connect to server (e.g., www.example.com on port 443)
    HTTPSafe::Client client(io_context, host, "443");

    // Receive and print the HTTP response
    client.read_http_response();
    std::cout << "Job done." << std::endl;
  }
  catch(std::exception& e) {
    std::cerr << "Error: " << e.what();
    return 1;
  }

  return 0;
}