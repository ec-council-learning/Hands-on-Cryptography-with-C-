#include "utils.hpp"

int nextversion::getnumber(std::istream& iss)
{
    int value;
    while (! (std::cin >> value)) {
        std::cout << std::endl 
                  << "Please, enter a valid number: ";
    }

    return value;
}

int nextversion::getnumber(std::istream& iss, int min, int max)
{
    int value;
    while (! (std::cin >> value) || value < min || value > max) {
        std::cout 
            << std::endl 
            << "Please, enter a valid number "
            << "[" << std::to_string(min) << "-" << std::to_string(max) << "] : ";
    }

    return value;
}