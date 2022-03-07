#include "../../include/Encryption/encryption.h"
#include <iostream>
#include <algorithm>

using namespace krypto;

int main()
{
    bool done = false;
    while (!done)
    {
        std::string input = "";
        std::getline(std::cin, input);
        if (input == "quit")
        {
            done = true;
            break;
        }
        std::transform(input.begin(), input.end(), input.begin(), ::toupper);
        encryption::runCommand(input);
    }

    return 0;
}