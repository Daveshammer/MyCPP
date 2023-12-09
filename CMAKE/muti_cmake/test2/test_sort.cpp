#include <iostream>
#include "sort.h"

int main()
{
    int a[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    // selet_sort(a, 0, 9);
    quick_sort(a, 0, 9);
    for (int i = 0; i < 10; i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}