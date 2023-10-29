#include <iostream>
#include <string>
#include <cctype>

int main()
{
    std::string message = "HELLO W0RLD";
    unsigned int checksum = 0;
    for (const auto& character : message) {
        checksum += character;
    }

    std::cout << "The checksum is: "
              << checksum
              << std::endl;

    return 0;
}