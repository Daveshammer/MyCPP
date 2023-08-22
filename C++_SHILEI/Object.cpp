#include <iostream>
using namespace std;

class Test
{
public:
    Test(int a = 10) :ma(a) {cout << "Test(int)" << endl;}
    ~Test() {cout << "~Test()" << endl;}
    Test(const Test &t) :ma(t.ma) {cout << "Test(const Test &t)" << endl;}
    Test& operator=(const Test &t) {ma = t.ma; cout << "Test& operator=(const Test &t)" << endl; return *this;}
    int getData() const {return ma;}
private:
    int ma;
};

/*
1.函数参数传递过程中，对象优先按引用传递，不要按值传递
2.函数返回对象的时候，应该优先返回一个临时对象，而不要返回一个定义过的对象（编译器可能已经优化）
3.接受返回值时对象的函数调用的时候，优先按初始化的方式接受，不要按赋值的方式接受
*/
Test GetObject(Test t) // 传引用可以避免 实参 =》 形参 的拷贝构造
{
    int val = t.getData();
    // Test tmp(val);
    // return tmp; // 编译器可能优化为 return Test(val);
    return Test(val);
}

int main()
{
    Test t1;
    Test t2;
    /*
    函数调用，实参 =》 形参，拷贝构造形参t
    函数返回时，拷贝构造可能被优化
    */
    t2 = GetObject(t1);
    // Test t2 = GetObject(t1); // 直接构造，避免Test& operator=(const Test &t

    return 0;
}