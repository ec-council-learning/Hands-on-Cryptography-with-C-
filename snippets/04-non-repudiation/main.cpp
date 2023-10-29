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

    std::string proof;
    proof.append("checksum:");
    proof.append(std::to_string(cs));

    std::cout << "The proof is '" << proof << "'" << std::endl;
    return 0;
}
