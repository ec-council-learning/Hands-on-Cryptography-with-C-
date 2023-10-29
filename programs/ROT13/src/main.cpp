#include <iostream>
#include "rot13.h"

int main()
{
    std::string input;
    std::cout << "Enter a message to encrypt: ";
    std::getline(std::cin, input);

    std::string cipher = rot13::rotate(input);

    std::cout << "The encrypted message is: "
              << cipher
              << std::endl;

    return 0;
}