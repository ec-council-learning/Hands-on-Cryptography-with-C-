#include "rot13.h"

namespace rot13 {

std::string rotate(std::string input) 
{
    // platform specific offset for alphabet
    unsigned int offset = 'a' - 1;

    std::string output;
    for (const auto& character : input) {
        if (0 == isalpha(character)) {
            output.append(1, character);
            continue;
        }

        if ((tolower(character) - offset) < 14) {
            // add 13
            output.append(1, character + 13);
        }
        else {
            // take 13
            output.append(1, character - 13);
        }
    }

    return output;
}

}