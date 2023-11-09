#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>

std::tuple<double, char, std::string> get_student(int id)
{
    if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
    if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
    if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
    throw std::invalid_argument("id");
}

int main()
{
    //按下标取值
    const auto student0 = get_student(0);
    std::cout << "ID: 0, "
        << "GPA: " << std::get<0>(student0) << ", "
        << "grade: " << std::get<1>(student0) << ", "
        << "name: " << std::get<2>(student0) << '\n';

    //按类型取值
    const auto student1 = get_student(1);
    std::cout << "ID: 1, "
        << "GPA: " << std::get<double>(student1) << ", "
        << "grade: " << std::get<char>(student1) << ", "
        << "name: " << std::get<std::string>(student1) << '\n';

    // tie
    double gpa2;
    char grade2;
    std::string name2;
    std::tie(gpa2, grade2, name2) = get_student(2);
    std::cout << "ID: 2, "
        << "GPA: " << gpa2 << ", "
        << "grade: " << grade2 << ", "
        << "name: " << name2 << '\n';

    // 结构化绑定
    auto [gpa3, grade3, name3] = get_student(2);
    std::cout << "ID: 3, "
        << "GPA: " << gpa3 << ", "
        << "grade: " << grade3 << ", "
        << "name: " << name3 << '\n';
}