#include <iostream>
#include "calc.h"

int main()
{
    std::cout << "Hello, World!" << std::endl;
    std::cout << "1 + 2 = " << add(1, 2) << std::endl;
    std::cout << "1 - 2 = " << subtract(1, 2) << std::endl;
    std::cout << "1 * 2 = " << mutiply(1, 2) << std::endl;
    std::cout << "1 / 2 = " << divide(1, 2) << std::endl;
    return 0;
}