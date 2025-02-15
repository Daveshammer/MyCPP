#include <iostream>

struct X {
    void f(int a, double b) const {
        std::cout << "X::f " << a << " " << b << '\n';
    }
    void f(int a, double b, int c) const {
        std::cout << "X::f (2) " << a << " " << b << " " << c << '\n';
    }
};

template<typename... Types>
using int_t = int;

// 默认版本
template<typename T, typename Enable = void>
struct f_impl {
    static void f(T&, int, double) {
        std::cout << "默认\n";
    }
    static void f(T&, int, double, double) {
        std::cout << "默认2\n";
    }
};

// 特化版本：检查是否存在 f(int, double)
template<typename T>
struct f_impl < T, std::void_t<decltype(std::declval<T>().f(int{}, double{})) >> {
    static void f(T& t, int a, double b) {
        t.f(a, b);
    }
};

// 特化版本：检查是否存在 f(int, double, int)
template<typename T>
struct f_impl < T, ::int_t<decltype(std::declval<T>().f(int{}, double{}, int{})) >> {
    static void f(T& t, int a, double b, int c) {
        t.f(a, b, c);
    }
};

// 重载的 f 函数：两个参数
template<typename T>
void f(T& t, int a, double b) {
    return f_impl<T, void>::f(t, a, b);  // 调用 f_impl 的静态成员函数
}

// 重载的 f 函数：三个参数
template<typename T>
void f(T& t, int a, double b, int c) {
    return f_impl<T, int>::f(t, a, b, c);  // 调用 f_impl 的静态成员函数
}

struct Y {
    // Y 没有任何成员函数 f
};

int main() {
    X x;
    Y y;
    f(x, 1, 2);       // 调用 X::f(int, double)
    f(x, 1, 2, 3);    // 调用 X::f(int, double, int)
    f(y, 1, 2);       // 输出 "默认"
    f(y, 1, 2, 3);    // 输出 "默认2"
}
