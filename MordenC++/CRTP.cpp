#include <iostream>

template <typename Derived>
class Base {
public:
    void doSomething() {
        static_cast<Derived*>(this)->impl();
    }
};

class DerivedA : public Base<DerivedA> {
public:
    void impl() {
        std::cout << "DerivedA implementation\n";
    }
};

class DerivedB : public Base<DerivedB> {
public:
    void impl() {
        std::cout << "DerivedB implementation\n";
    }
};

int main() {
    DerivedA a;
    DerivedB b;

    a.doSomething(); // 输出: DerivedA implementation
    b.doSomething(); // 输出: DerivedB implementation
    return 0;
}

