#include <iostream>
#include "head.h"

int main()
{
    int a = 20;
    int b = 12;
    std::cout << "a + b = " << add(a, b) << std::endl;
    std::cout << "a - b = " << subtract(a, b) << std::endl;
    std::cout << "a * b = " << mutiply(a, b) << std::endl;
    std::cout << "a / b = " << divide(a, b) << std::endl;
}