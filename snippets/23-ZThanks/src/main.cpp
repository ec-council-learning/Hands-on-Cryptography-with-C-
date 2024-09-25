// src/main.cpp
#include <iostream> // std::cout
#include <string> // std::string
#include "credits.h" // ztx::ZCredits

int print_usage() {
  std::cout
    << "Usage: ztx [-h] <message>\n"
    << "  e.g: ztx \"Thank you all!\"\n"
    << "\nFLAGS: \n"
    << "  -h: Prints this help message and usage examples.\n";
  return 1;
}

int main(int argc, char* argv[])
{
  // make sure we have a thank you message
  std::string flag;
  if (argc == 1) flag = "Thank you, dear readers!";
  else flag = std::string(argv[1]);

  // also accepted are: `ztx -h` and `ztx help`
  if (flag == "-h" || flag == "help")
    return print_usage();

  // use the default message or the one provided
  std::string message = flag;

  // create the credits instance, this initializes ciphers
  auto cred = new ztx::ZCredits(message);

  // Print the credits message (encrypted of course)
  std::cout << "CREDITS: " << std::endl
            << "------------"
            << std::endl << std::endl
            << static_cast<std::string>(*cred)
            << std::endl;

  return 0;
}