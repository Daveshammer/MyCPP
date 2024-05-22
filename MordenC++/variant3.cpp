#include <string>
#include <iostream>
#include <variant>

class MyType
{
public:
    MyType() { std::cout << "MyType::MyType\n"; }
    ~MyType() { std::cout << "MyType::~MyType\n"; }
};

class OtherType
{
public:
    OtherType() { std::cout << "OtherType::OtherType\n"; }
    OtherType(const OtherType&) { 
        std::cout << "OtherType::OtherType(const OtherType&)\n"; 
    }
    ~OtherType() { std::cout << "OtherType::~OtherType\n"; }
};

int main() 
{
    /*
    我们使用MyType的默认值来初始化variant；然后使用OtherType的实例更改variant的值。
    先调用MyType的析构函数，然后调用OtherType赋值运算符，稍后销毁临时对象，
    最后程序运行结束时销毁存储在variant中的对象。
    */
    std::variant<MyType, OtherType> v;
    std::cout << "---------------" << std::endl;
    v = OtherType();
}