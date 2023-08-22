#include <iostream>
using namespace std;

/*
抽象类（有纯虚函数的类） / 虚基类（被虚继承的类）vbptr和vbtable
virtual
1.修饰成员方法是虚函数
2.可以修饰继承方式，是虚继承。被虚继承的类，称作虚基类
*/

class A
{
public:
    virtual void func() { cout << "A::func()" << endl; }
    void operator delete(void *p)
    {
        cout << "A::operator delete() p:" << p << endl;
        free(p);
    }
private:
    int ma;
};
class B : virtual public A
{
public:
    virtual void func() { cout << "B::func()" << endl; }
    void* operator new(size_t size)
    {
        void *p = malloc(size);
        cout << "B::operator new() p:" << p << endl;
        return p;
    }
private:
    int mb;
};

int main()
{
    // 基类指针指向派生类对象，永远指向派生类的基类部分数据的起始地址
    A *p = new B();
    p->func();
    cout << "main p:" << p << endl;
    delete p;

    // 没有虚继承时
    // cout << sizeof(A) << endl; // 4:ma
    // cout << sizeof(B) << endl; // 16:vbptr(8) + ma(4) + mb(4)

    return 0;
}