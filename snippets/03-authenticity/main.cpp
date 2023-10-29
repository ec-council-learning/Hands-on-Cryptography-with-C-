#include <iostream>
#include <string>
#include <cctype>

unsigned int checksum(std::string message) {
    unsigned int checksum = 0;

    for (const auto& character : message) {
        checksum += character;
    }

    return checksum;
}

int main()
{
    std::string message = "HELLO WORLD";
    std::string author = " by Gregory Saive";

    std::string signed_message = message.append(author);
    unsigned int cs = checksum(signed_message);

    if (cs != 2350) {
        std::cout << "The message is NOT authentic!" << std::endl;
        return 1;
    }

    std::cout << "The message is authentic!" << std::endl;
    return 0;
}