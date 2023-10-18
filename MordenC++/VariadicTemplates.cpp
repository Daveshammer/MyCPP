#include <iostream>

// 基础情况：没有参数时返回0
int sum() {
    return 0;
}

// 递归情况：计算第一个参数加上剩余参数的和
template<typename T, typename... Args>
T sum(T first, Args... args) {
    return first + sum(args...);
}

int main() {
    int result = sum(1, 2, 3, 4, 5);
    std::cout << "Sum: " << result << std::endl;
    return 0;
}
