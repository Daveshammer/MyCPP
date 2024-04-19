#include <iostream>
#include <string>
#include <tuple>

std::tuple<std::string, int> CreatePerson()
{
    return {"Tom", 20};
}

int main()
{
    auto [name, age] = CreatePerson();
    std::cout << "name: " << name << ", age: " << age << std::endl;
    return 0;
}