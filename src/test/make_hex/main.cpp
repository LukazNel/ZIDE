#include <iostream>
#include "zutils.h"

int main() {
    std::cout << "Enter a number: ";
    std::string In;
    std::cin >> In;
    std::cout << "Out: " << std::stoi(In, nullptr, 16) << std::endl;
    return 0;
}
