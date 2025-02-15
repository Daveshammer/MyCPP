#include <iostream>
#include <iterator>
#include <typeinfo>

// 自定义迭代器类
class MyIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = int;
    using difference_type = std::ptrdiff_t;
    using pointer = int*;
    using reference = int&;
};

int main() {
    // 使用 std::iterator_traits 提取特性
    std::cout << "MyIterator category: "
        << typeid(typename std::iterator_traits<MyIterator>::iterator_category).name() << "\n";

    std::cout << "int* category: "
        << typeid(typename std::iterator_traits<int*>::iterator_category).name() << "\n";

    return 0;
}
