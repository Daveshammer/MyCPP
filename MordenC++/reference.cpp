#include <iostream>

class Resource {
private:
    int* data;

public:
    // 构造函数
    Resource(int value) : data(new int(value)) {
        std::cout << "Resource acquired (" << this << "), Value = " << *data << std::endl;
    }

    // 拷贝构造函数
    Resource(const Resource& other) : data(new int(*other.data)) {
        std::cout << "Copied resource (" << this << ") from (" << &other << "), Value = " << *data << std::endl;
    }

    // 移动构造函数
    Resource(Resource&& other) noexcept : data(other.data) {
        other.data = nullptr;
        std::cout << "Moved resource (" << this << ") from (" << &other << ")" << std::endl;
    }

    // 拷贝赋值运算符
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            delete data;
            data = new int(*other.data);
            std::cout << "Copy assigned resource (" << this << ") from (" << &other << "), Value = " << *data << std::endl;
        }
        return *this;
    }

    // 移动赋值运算符
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
            std::cout << "Move assigned resource (" << this << ") from (" << &other << ")" << std::endl;
        }
        return *this;
    }

    // 析构函数
    ~Resource() {
        delete data;
        std::cout << "Resource released (" << this << ")" << std::endl;
    }

    // 左值引用限定符的成员函数
    void print()& {
        std::cout << "Left-value reference: Data = " << (data ? *data : 0) << " (" << this << ")" << std::endl;
    }

    // 右值引用限定符的成员函数
    void print()&& {
        std::cout << "Right-value reference: Data = " << (data ? *data : 0) << " (" << this << ")" << std::endl;
    }

    // 带 const 的左值引用限定符的成员函数
    void print() const& {
        std::cout << "Const left-value reference: Data = " << (data ? *data : 0) << " (" << this << ")" << std::endl;
    }

    // 带 const 的右值引用限定符的成员函数
    void print() const&& {
        std::cout << "Const right-value reference: Data = " << (data ? *data : 0) << " (" << this << ")" << std::endl;
    }
};

int main() {
    Resource r(42); // 创建一个左值对象
    r.print();      // 调用左值引用限定符的成员函数

    Resource(11).print(); // 创建一个临时右值对象并调用右值引用限定符的成员函数

    const Resource cr(10); // 创建一个常量左值对象
    cr.print();          // 调用带 const 的左值引用限定符的成员函数

    std::move(cr).print(); // 使用 std::move 将常量左值转换为右值，并调用带 const 的右值引用限定符的成员函数

    Resource another_r(20);
    another_r.print(); // 调用左值引用限定符的成员函数

    std::move(another_r).print(); // 使用 std::move 将左值转换为右值，并调用右值引用限定符的成员函数

    return 0;
}
